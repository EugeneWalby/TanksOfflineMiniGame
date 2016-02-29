
#include "TANK.h"
#include "PLAYER_TANK.h"
#include "ENEMY_TANK.h"
#include "BULLET.h"
#include "HGE_LIB.h"
#include "BLOCK.h"

FILE *fp;

Tank* player1;
Tank* player2;
//list<Enemy_tank> enemy_vec;
list<Bullet*> bullet_vec;
list<Block*> blocks;

HTEXTURE Bul;
HTEXTURE BLOCK;
hgeFont *hF;     // Указатель для отображения текстов с помощью растрового шрифта
hgeFont *HF;
HGE* hge = 0;
int count1=0;
int count2=0;
char buf[1000];
int death1=0, death2=0;
bool flag=true;
bool flag2=true;

bool STOP=0;

int time_hit1=0;
int time_hit2=0;
bool hit1=0;
bool hit2=0;
float hit1_x, hit2_x, hit1_y, hit2_y;

//Explosion
HTEXTURE	g_tExplosion		= 0;

//Sounds
HEFFECT	    knock		        = 0;
HEFFECT		g_eGunshot			= 0;
HEFFECT     Music               = 0;

struct explosion
{
	hgeAnimation*	Animation;
	float		x;
	float		y;
};
list<explosion> Explosions;
HEFFECT		g_eExplosion		= 0;

void CreateExplosion(const float &x, const float &y)
{
	explosion exp;
	exp.Animation = new hgeAnimation(g_tExplosion,5,10,0,0,118,118);
	exp.Animation->SetHotSpot(59,59);
	exp.Animation->Play();
	exp.x=x;
	exp.y=y;
	Explosions.push_back(exp);

	hge->Effect_PlayEx(g_eExplosion,100,0,hge->Random_Float(1,3));
}

bool FrameFunc() // Ф-ция кадра, вызывается один раз за кадр
{
	if(STOP){
		Sleep(10000);
		return true;
	}
	float dt = hge->Timer_GetDelta();

	++count1;
	++count2;
	if(count1 >= 100){
		count1 = 0;
		flag = true;
	}
	if(count2 >= 100){
		count2 = 0;
		flag2 = true;
	}

	++time_hit1;
	if(time_hit1 >= 50){
		time_hit1 = 0;
		hit1 = false;
	}
	++time_hit2;
	if(time_hit2 >= 50){
		time_hit2 = 0;
		hit2 = false;
	}

	if(hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	
		player1->control1();
		player2->control2();
	
	//Collision Player vs Player
		float next_y1 = player1->Tank::get_Y() + (player1->Tank::get_dY() * 0.75f);
		float next_y2 = player2->Tank::get_Y() + (player2->Tank::get_dY() * 0.75f);

		float next_x1 = player1->Tank::get_X() + (player1->Tank::get_dX() * 0.75f);
		float next_x2 = player2->Tank::get_X() + (player2->Tank::get_dX() * 0.75f);

		if((fabs(next_y1 - next_y2) <= 50 && (fabs(next_x1 - next_x2) <= 50))){
			player1->Tank::set_dX(0.0f);
			player1->Tank::set_dY(0.0f);

			player2->Tank::set_dX(0.0f);
			player2->Tank::set_dY(0.0f);
		}

	//Collision Player vs Block
		for(list<Block*>::iterator i=blocks.begin(); i != blocks.end(); ++i){
			if((fabs(next_y1 - (*i)->get_Y()) <= 47 && (fabs(next_x1 - (*i)->get_X()) <= 47))){
				player1->Tank::set_dX(0.0f);
				player1->Tank::set_dY(0.0f);
			}
			else if((fabs(next_y2 - (*i)->get_Y()) <= 47 && (fabs(next_x2 - (*i)->get_X()) <= 47))){
				player2->Tank::set_dX(0.0f);
				player2->Tank::set_dY(0.0f);
			}
		}

		//Action_Tank tmp=->update();
		player1->update();
		player2->update();

		
		if(hge->Input_KeyDown(HGEK_SPACE))
		{	
			if(flag == true){
				//Single shot
				Bullet* bullet;
				if(player1->get_state() == UP)
					{ bullet = new Bullet(10, 10, player1->get_X()-6, player1->get_Y()-30, Bul, player1->get_state()); }
				else if(player1->get_state() == DOWN)
					{ bullet = new Bullet(10, 10, player1->get_X()-5, player1->get_Y()+30, Bul, player1->get_state()); }
				else if(player1->get_state() == LEFT)
					{ bullet = new Bullet(10, 10, player1->get_X()-30, player1->get_Y()-5, Bul, player1->get_state()); }
				else if(player1->get_state() == RIGHT)
					{ bullet = new Bullet(10, 10, player1->get_X()+30, player1->get_Y()-5, Bul, player1->get_state()); }
						
				bullet_vec.push_back(bullet);
				hge->Effect_PlayEx(g_eGunshot,100,0,hge->Random_Float(1,1.5));
				flag = false;
				count1 = 0;
			}
		}

		if(hge->Input_KeyDown(HGEK_ENTER))
		{
			if(flag2 == true){
				//Single shot
				Bullet* bullet;
				if(player2->get_state() == UP)
					{ bullet = new Bullet(10, 10, player2->get_X()-6, player2->get_Y()-30, Bul, player2->get_state()); }
				else if(player2->get_state() == DOWN)
					{ bullet = new Bullet(10, 10, player2->get_X()-5, player2->get_Y()+30, Bul, player2->get_state()); }
				else if(player2->get_state() == LEFT)
					{ bullet = new Bullet(10, 10, player2->get_X()-30, player2->get_Y()-5, Bul, player2->get_state()); }
				else if(player2->get_state() == RIGHT)
					{ bullet = new Bullet(10, 10, player2->get_X()+30, player2->get_Y()-5, Bul, player2->get_state()); }
						
				bullet_vec.push_back(bullet);
				hge->Effect_PlayEx(g_eGunshot,100,0,hge->Random_Float(1,1.5));
				flag2 = false;
				count2 = 0;
			}
		}

		//Bullet fly
		for(list<Bullet*>::iterator i= bullet_vec.begin(); i != bullet_vec.end(); /**/)
	    {
				(*i)->update();

			if((*i)->get_bulletX() > 800 || (*i)->get_bulletX() < 0 || (*i)->get_bulletY() < 0 || (*i)->get_bulletY() > 600) i = bullet_vec.erase(i);
			else i++;
	    }


		//Collision Bullet vs Player
	if(!bullet_vec.empty())
	{
		float y1 = player1->Tank::get_Y();
		float y2 = player2->Tank::get_Y();

		float x1 = player1->Tank::get_X();
		float x2 = player2->Tank::get_X();

		for(list<Bullet*>::iterator i = bullet_vec.begin(); i != bullet_vec.end(); /**/)
		{
			bool bHit = false;

				if((fabs(y1 - (*i)->get_bulletY())) <= 25 && (fabs(x1 - (*i)->get_bulletX())) <= 25)
				{
					hge->Effect_PlayEx(knock,100,0,hge->Random_Float(1,1.5));

					hit1 = true;
					time_hit1 = 0;
					hit1_x = player1->get_X()-25;
					hit1_y = player1->get_Y()-45;

					player1->set_health(player1->get_health() - (*i)->get_damage());
					delete (*i);
					i	 = bullet_vec.erase(i);
					bHit = true;
					continue;
				}
				if((fabs(y2 - (*i)->get_bulletY())) <= 25 && (fabs(x2 - (*i)->get_bulletX())) <= 25)
				{
					hge->Effect_PlayEx(knock,100,0,hge->Random_Float(1,1.5));

					hit2 = true;
					time_hit2 = 0;
					hit2_x = player2->get_X()+25;
					hit2_y = player2->get_Y()-45;

					player2->set_health(player2->get_health() - (*i)->get_damage());
					delete (*i);
					i	 = bullet_vec.erase(i);
					bHit = true;
					continue;
				}
			if(!bHit) i++;
		}
	}

	// Collision Bullet vs Block
	if(!bullet_vec.empty())
	{
		for(list<Bullet*>::iterator i = bullet_vec.begin(); i != bullet_vec.end(); /**/)
		{
			bool bHit = false;
			for(list<Block*>::iterator j = blocks.begin(); j != blocks.end(); ++j)
			{
	
				float y1 = (*i)->get_bulletY();
				float y2 = (*j)->get_Y();

				float x1 = (*i)->get_bulletX();
				float x2 = (*j)->get_X();

				if((fabs(y1 - y2) <= 25) && (fabs(x1 - x2) <= 25)){
					
					CreateExplosion((*i)->get_bulletX(), (*i)->get_bulletY());
					delete (*i);
					i	 = bullet_vec.erase(i);
					delete (*j);
					j	 = blocks.erase(j);
					bHit = true;
					break;
				};
			}
			if(!bHit) i++;
		}
	}


	// Collision Bullet vs Bullet
	if(bullet_vec.size() >= 2 )
	{
		for(list<Bullet*>::iterator i = bullet_vec.begin(); i != bullet_vec.end(); /**/)
		{
			bool bHit = false;
			for(list<Bullet*>::iterator j = bullet_vec.begin(); j != bullet_vec.end() && (*i) != (*j); ++j)
			{
	
				float y1 = (*i)->get_bulletY();
				float y2 = (*j)->get_bulletY();

				float x1 = (*i)->get_bulletX();
				float x2 = (*j)->get_bulletX();

				if((fabs(y1 - y2) <= 8) && (fabs(x1 - x2) <= 8)){
					
					CreateExplosion((*i)->get_bulletX(), (*i)->get_bulletY());
					delete (*i);
					i	 = bullet_vec.erase(i);
					delete (*j);
					j	 = bullet_vec.erase(j);
					bHit = true;
					break;
				};
			}
			if(!bHit) i++;
		}
	}

	//Explosions
	for(list<explosion>::iterator i = Explosions.begin(); i != Explosions.end(); /**/)
	{
		if((*i).Animation->GetFrame() == 4)
		{
			delete (*i).Animation;
			i = Explosions.erase(i);
		}
		else
		{
			(*i).Animation->Update(dt);
			i++;
		}
	}

	//Check Player's health
		if(player1->get_health() <= 0)
		{
			++death1;
			player1->set_health(100);
			CreateExplosion(player1->get_X(), player1->get_Y());

			player1->set_X(-100);
			player1->set_Y(-100);
			int choice = rand()%3;

			if(choice == 0){
				player1->set_X(50);
				player1->set_Y(50);
			}
			else if(choice == 1){
				player1->set_X(50);
				player1->set_Y(550);
			}
			else {
				player1->set_X(750);
				player1->set_Y(550);
			}
		}
		if(player2->get_health() <= 0)
		{
			++death2;
			player2->set_health(100);
			CreateExplosion(player2->get_X(), player2->get_Y());

			player2->set_X(-100);
			player2->set_Y(-100);
			int choice = rand()%3;

			if(choice == 0){
				player2->set_X(750);
				player2->set_Y(50);
			}
			else if(choice == 1){
				player2->set_X(50);
				player2->set_Y(550);
			}
			else {
				player2->set_X(750);
				player2->set_Y(550);
			}
		}

		//if (tmp == EXPLOSE_TANK){
		//	/*clock_t t=clock();
		//	while(t/CLOCKS_PER_SEC < 3.0){
		//		t = clock() - t;
		//	}*/
		//	++C;
		//	/*delete *i;
		//	player_vec.erase(find(player_vec.begin(), player_vec.end(), *i)	);
		//	*/
		//	break;
		//}else if (tmp == SHOT){
		//	
		//}


	//if (player_vec[0]->get_X()>=player_vec[1]->get_X()-15 && player_vec[0]->get_X()>=player_vec[1]->get_X()+15){
	//	//player_vec[0]->set_X(player_vec[1]->get_X()-1);
	//	player_vec[0]->set_dX(-player_vec[0]->get_dX());
	//	//player_vec[1]->set_X(player_vec[0]->get_X()-1);
	//	player_vec[1]->set_dX(-player_vec[1]->get_dX());

	//}
	
	return false;
}

bool RenderFunc()  // Ф-ция рендеринга, для рисования
{

	hge->Gfx_BeginScene();        // Начинает вывод графики
	hge->Gfx_Clear(0);            // Очищает экран, окрашивая его в цвет в формате ARGB 

	player1->render();
	player2->render();

	for(list<Bullet*>::iterator i=bullet_vec.begin(); i!=bullet_vec.end(); ++i)
	    (*i)->render();

	//Explosions
	for(list<explosion>::iterator i = Explosions.begin(); i != Explosions.end(); ++i)
	{
		(*i).Animation->Render((*i).x, (*i).y);
	}

	//Blocks
	for(list<Block*>::iterator i = blocks.begin(); i != blocks.end(); ++i)
	{
		(*i)->render();
	}

	if(hit1 == 1){
		hF->SetColor(0xF00FF000);
		hF->printf(hit1_x,  hit1_y, 100, "-10");
	}
	if(hit2 == 1){
		hF->SetColor(0xFFF00000);
		hF->printf(hit2_x,  hit2_y, 100, "-10");
	}
	hF->SetColor(0xF00FF000);
	hF->printf(390.0f,  10.0f, 50, "SCORE:");
	hF->printf(390.0f,  25.0f, 50, "|");
	hF->printf(390.0f,  35.0f, 50, "|");
	HF->printf(375.0f,  24.0f, 50, itoa(death1, buf, 10));
	HF->printf(403.0f,  24.0f, 50, itoa(death2, buf, 10));

	HF->SetColor(0xF0FFFF00);
	if(death1 == 3){
		hge->Gfx_Clear(0);
		HF->printf(400.0f,  200.0f, 50, "Player 2 WIN!");
		STOP = 1;
	}
	if(death2 == 3){
		hge->Gfx_Clear(0);
		HF->printf(400.0f,  200.0f, 50, "Player 1 WIN!");
		STOP = 1;
	}

	
	//hF->printf(250.0f,  100.0f, 100, itoa(count1, buf, 10));
	
	//...


	hge->Gfx_EndScene();          // Заканчивает вывод графики и обновляет экран, если это необходимо

	return false;
}

void HgeSetState() // Инициализация значений HGE
{
  hge->System_SetState(HGE_LOGFILE, "Танки.log");
  hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
  hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
  hge->System_SetState(HGE_TITLE, "Танки Оффлайн");

 
  hge->System_SetState(HGE_FPS, 100);
  hge->System_SetState(HGE_WINDOWED, false);
  hge->System_SetState(HGE_SCREENWIDTH, 800);
  hge->System_SetState(HGE_SCREENHEIGHT, 600);
 // hge->System_SetState(HGE_SCREENBPP, 50);
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	srand((unsigned)time(NULL));
	hge = hgeCreate(HGE_VERSION);  // Инициализация интерфейса HGE
	HgeSetState();  // Инициализация значений HGE

		
	if(hge->System_Initiate()){

		BLOCK=hge->Texture_Load("Block.jpg");
		//Block b[50];
		//int N_used = 0;
		////for(int i=0;i<50;++i) b[i] = new Block();
		////Работа с файлами
		//if(fopen("file.txt", "r")!= NULL)
		//	fp = fopen("file.txt", "r");
		//else
		//	fp = fopen("file.txt", "w");
		//N_used = fread(b, sizeof(Block*), 100, fp);
		//fclose(fp);

		//fp = fopen("file.txt", "w");
		//assert(N_used == 27);


		//Write Blocks
		for (int i=0; i<7; i++){
			blocks.push_back(new Block(250.0f +i*50.0f, 300.0f, BLOCK));
		}
		for (int i=0; i<=6; i++){
			if(i == 3) continue;
			blocks.push_back(new Block(400.0f, 150.0f+i*50.0f, BLOCK));
		}
		for (int i=0; i<=6; i++){
			blocks.push_back(new Block(100.0f, 150.0f+i*50.0f, BLOCK));
		}
		for (int i=0; i<=6; i++){
			blocks.push_back(new Block(700.0f, 150.0f+i*50.0f, BLOCK));
		}

		//for(list<Block*>::iterator j = blocks.begin();j != blocks.end();++j){
		//	b[N_used] = *j;
		//	++N_used;
		//}

		/*for(int i=0;i<N_used;++i){
			blocks.push_back(b[i]);
		}*/
		assert(blocks.size() == 27);

		hF=new hgeFont("font2.fnt");
		HF=new hgeFont("font1.fnt");
		HTEXTURE Texture = hge->Texture_Load("player1.png");
		HTEXTURE Texture2 = hge->Texture_Load("player2.png");
		Bul = hge->Texture_Load("bullet.png");
		player1=new Player_tank(-1.0f, 100.0f, 50.0f, 50.0f, Texture);
		player2=new Player_tank(-1.0f, 100.0f, 750.0f, 50.0f, Texture2);
		 //p = new Player_tank(-1.0f, 100.0f, 50.0f, 50.0f, Texture);
		assert(Texture != 0);

		//Explosion
		g_tExplosion	= hge->Texture_Load("Explosion-Sprite-Sheet.png");

		//Sounds
		g_eExplosion	= hge->Effect_Load("Boom1.mp3");
		g_eGunshot		= hge->Effect_Load("Shot.mp3");
		knock           = hge->Effect_Load("knock.mp3");
		Music           = hge->Effect_Load("battle_theme.mp3");
		hge->Effect_PlayEx(Music, 30, 0, 0, true);


		for(list<explosion>::iterator i = Explosions.begin(); i != Explosions.end(); /**/)
		{
			delete (*i).Animation;
			i = Explosions.erase(i);
		}

		//if(!p.Texture)
		//{
		//	// If one of the data files is not found, display
		//	// an error message and shutdown.
		//	MessageBox(NULL, "Can't load MENU.WAV, PARTICLES.PNG, green_arcan.png, red_arcan.png, starfield.png, font.png or van_den_bos - foregone_destruction.mp3", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		//	
		//	return 0;
		//}
		hge->System_Start();    // Запуск HGE

		//fwrite(b, sizeof(Block*), N_used, fp);
		//fclose(fp);
	}
	else
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);


	 return 0;
}

