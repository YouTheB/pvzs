#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "utils.h"
#include "pvzclass.h"
using namespace std;
vector<int> z[50];
ZombieType::ZombieType mr[] = { ZombieType::FlagZombie };
void read(PVZ* pvz)
{
	for (int i = 0; i < 40; i++)
	{
		if (i % 10 == 9)
			pvz->GetWave(i)->SetAll(mr, 1);
		else
			pvz->GetWave(i)->SetAll(mr, 1);
	}
	ifstream fin("D:\\PVZ\\list.txt");
	int n;
	fin >> n;
	for (int i = 1; i <= n; i++)
	{
		int m;
		fin >> m;
		for (int j = 1; j <= m; j++)
		{
			int a;
			fin >> a;
			z[i].push_back(a);
		}
	}
}
std::vector<Plant*> GetAllPlants(PVZ* pvz)
{
	std::vector<Plant*> rt;
	int n = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xB0);
	for (int i = 0; i < n; i++)
		if (!PVZ::Memory::ReadMemory<byte>(PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xAC) + 0x141 + 0x14C * i))
			rt.push_back(new Plant(i));
	return rt;
}

std::vector<Zombie*> GetAllZombies(PVZ* pvz)
{
	std::vector<Zombie*> rt;
	int n = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0x94);
	for (int i = 0; i < n; i++)
		if (!PVZ::Memory::ReadPointer(pvz->BaseAddress + 0x90, 0xEC + 0x15C * i))
			rt.push_back(new Zombie(i));
	return rt;
}
void onFire(Projectile* proj)
{
	cerr << "fire " << proj->Row << endl;
}
PlantType::PlantType sj()
{
	int t = rand() % 10;
	switch (t)
	{
	case 0:
		return PlantType::CherryBomb;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		return PlantType::PotatoMine;
	case 9:
		return PlantType::Doomshroon;
	case 6:
		return PlantType::Squash;
	case 7:
	case 8:
		return PlantType::Jalapeno;
	}
}
void onRemove(Projectile* proj)
{
	if (proj->Type != ProjectileType::Cabbage)
		return;
	cerr << "remove " << proj->Row << endl;
	cerr << "remove on " << proj->X << endl;
	double x = (proj->X - 40.0) / 80.0;
	int col = (int)(x + 0.5);
	cerr << "create on " << proj->Row << " " << col << endl;
	if (col > 9)
		return;
	PlantType::PlantType type = sj();

	Plant* plant=Creater::CreatePlant(type, proj->Row, col);
	plant->Sleeping = false;
	plant->ShootingCountdown = 1;
	plant->AttributeCountdown = 1;
	plant->EffectiveCountdown = 1;
	plant->ShootOrProductCountdown = 1;
}
void onPlant(Plant* plant)
{
	cerr << plant->Row << "," << plant->Column << " " << ToString(plant->Type) << " x: " << plant->X << " y: " << plant->Y << endl;
	if (plant->Type == PlantType::Cabbagepult)
	{
		Utils::SetPlantCost(plant->Type, Utils::GetPlantCost(plant->Type) + 1000);
	}
}
void onWave(int wave)
{
	if (wave == 0)
		return;
	if (wave % 10 == 0)
	{
		Creater::CreateCaption("本视频仅在BiliBili发布！", 50, CaptionStyle::CenterRed,3000);
	}
	int lim = z[wave].size();
	cerr << "wave " << wave << " lim " << lim << endl;
	for (int i = 0; i < lim; i++)
	{
		ZombieType::ZombieType type = (ZombieType::ZombieType)(z[wave][i]);
		int row = rand() % 5;
		Creater::CreateZombie(type, row, 10 + rand() % 2);
	}
}

void onSpawn(PVZ::Zombie* zombie)
{
	if (zombie->Type >= 26 && zombie->Type <= 31)
		zombie->State = 3;
}
int GetN(PVZ* pvz)
{
	int rt = 0;
	int n = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0x94);
	for (int i = 0; i < n; i++)
		if (!PVZ::Memory::ReadPointer(pvz->BaseAddress + 0x90, 0xEC + 0x15C * i))
			rt++;
	return rt;
}
int main()
{
	srand(time(NULL));//初始化随机种子
	//init，必写，初始化
	Creater::AsmInit();
	DWORD pid = ProcessOpener::Open();//寻找游戏进程
	cerr << pid << endl;
	if (pid)
	{
		PVZ *pvz = new PVZ(pid);//实例化游戏对象
		cerr << pvz->BaseAddress << endl;
		while (!pvz->BaseAddress);
		Sleep(1000);
		read(pvz);
		EnableBackgroundRunning();
		AutoCollect(pvz, 0);
		EventHandler e(pvz);
		e.RegisterProjectileRemoveEvent(onRemove);
		e.RegisterPlantPlantEvent(onPlant);
		e.RegisterZombieSpawnEvent(onSpawn);
		e.RegisterLevelWaveEvent(onWave);
		Utils::SetPlantCost(PlantType::Cabbagepult, 750);
		PVZ::Memory::WriteMemory<int>(0x532FDC, 600);
		while (1)
		{
			Sleep(10);
			e.Run();
			vector<Plant*> plants = GetAllPlants(pvz);
			for (Plant* plant : plants)
			{
				if (plant->Type == PlantType::Doomshroon)
				{
					if (plant->AttributeCountdown > 1 || plant->EffectiveCountdown > 1 || plant->ShootingCountdown > 1 || plant->ShootOrProductCountdown > 1)
					{
						plant->ShootingCountdown = 1;
						plant->AttributeCountdown = 1;
						plant->EffectiveCountdown = 1;
						plant->ShootOrProductCountdown = 1;
					}
				}
			}
			vector<Zombie*> zombies = GetAllZombies(pvz);
			for (Zombie* zombie : zombies)
			{
				if(zombie->FrozenCountdown>1)
					zombie->FrozenCountdown = 1;
				if (zombie->Type == ZombieType::Imp)
					zombie->State = 3;
			}

			int n = GetN(pvz);
			//cerr << "now has " << n << " wave " << pvz->RefreshedWave << endl;
			if (n != 0 && pvz->RefreshedWave != 0)
				if (z[pvz->RefreshedWave].size() / 2 < n)
					pvz->NextWaveCountdown = 1800;
			//cerr << pvz->NextWaveCountdown << endl;

		}
		delete pvz;//关闭句柄
	}

	return 0;
}
