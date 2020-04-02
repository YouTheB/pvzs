#include "pvzclass.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "utils.h"
using namespace std;
vector<int> z[40];
void onPlant(PVZ::Plant* plant)
{
	if (plant->Hp == 301)
		return;
	if (plant->Type == PlantType::Doomshroon)
	{
		Creater::CreatePlant((PlantType::PlantType)(rand() % 64 / 8+PlantType::GatlingPea), plant->Row, plant->Column);
		plant->Hp = -10000;
	}
	if (plant->Type == PlantType::Peashooter)
	{
		PlantType::PlantType type=PlantType::Sprout;
		switch (rand()%7)
		{
		case 0:
			type = PlantType::Peashooter;
			break;
		case 1:
			type = PlantType::Repeater;
			break;
		case 2:
			type = PlantType::Threepeater;
			break;
		case 3:
			type = PlantType::GatlingPea;
			break;
		case 4:
			type = PlantType::SnowPea;
			break;
		case 5:
			type = PlantType::SplitPea;
			break;
		case 6:
			type = PlantType::LeftRepeater;
			break;
		}
		Creater::CreatePlant(type, plant->Row, plant->Column)->Hp = 301;
		plant->Hp = -10000;
	}
	if (plant->Type == PlantType::Cabbagepult)
	{
		PlantType::PlantType type = PlantType::Sprout;
		switch (rand()%4)
		{
		case 0:
			type = PlantType::Cabbagepult;
			break;
		case 1:
			type = PlantType::Kernelpult;
			break;
		case 2:
			type = PlantType::Melonpult;
			break;
		case 3:
			type = PlantType::WinterMelon;
			break;
		}
		Creater::CreatePlant(type, plant->Row, plant->Column)->Hp = 301;
		plant->Hp = -10000;
	}
}
void onWave(int wave)
{
	if(wave%4==0)
	Creater::CreateCaption("本视频仅在BiliBili发布！从不在快手抖音优酷等发视频！\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
		strlen("本视频仅在BiliBili发布！从不在快手抖音优酷等发视频！\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"), CaptionStyle::TopYellow);
	if(wave%4==1)
	Creater::CreateCaption("本视频仅在BiliBili发布！从不在快手抖音优酷等发视频！\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
		strlen("本视频仅在BiliBili发布！从不在快手抖音优酷等发视频！\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"), CaptionStyle::Lowerpart);
	if(wave%4==2)
	Creater::CreateCaption("本视频仅在BiliBili发布！从不在快手抖音优酷等发视频！\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
		strlen("本视频仅在BiliBili发布！从不在快手抖音优酷等发视频！\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"), CaptionStyle::Lowermiddle);
	if(wave%4==3)
	Creater::CreateCaption("本视频仅在BiliBili发布！从不在快手抖音优酷等发视频！\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
		strlen("本视频仅在BiliBili发布！从不在快手抖音优酷等发视频！\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"), CaptionStyle::Bottom);
	if (wave == 0)
		return;
	char ha[100] = {0};
	if (wave % 10)
		sprintf_s(ha, "第 %d 波来了！生成了 %d 只僵尸！\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", wave, z[wave].size());
	else
	{
		sprintf_s(ha, "本视频仅在BiliBili发布！从不在快手抖音优酷等发视频！\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
	}
	Creater::CreateCaption(ha, 50, wave % 10 ? CaptionStyle::BottomWhite : CaptionStyle::CenterRed);
	cerr << ha << " " << strlen(ha) << endl;
	int lim = z[wave].size();
	cerr << "wave " << wave << " lim " << lim << endl;
	for (int i = 0; i < lim; i++)
	{
		ZombieType::ZombieType type = (ZombieType::ZombieType)(z[wave][i]);
		int row = rand() % 4;
		if (row > 1)
			row += 2;
		Creater::CreateZombie(type, row, 10+rand()%2);
	}
}
void onSpawn(PVZ::Zombie* zombie)
{
	if (zombie->Type >= 26 && zombie->Type <= 31)
		zombie->State = 3;
	if (zombie->Row == 2 || zombie->Row == 3)
		zombie->State = 3;
}
void read()
{
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
int GetAllZombies(PVZ* pvz)
{
	int rt=0;
	int n = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0x94);
	for (int i = 0; i < n; i++)
		if (!PVZ::Memory::ReadPointer(pvz->BaseAddress + 0x90, 0xEC + 0x15C * i))
			rt++;
	return rt;
}
int main()
{
	DWORD pid = ProcessOpener::Open();
	while (!pid)
	{
		cout << "didn't found pid." << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	}
	cout << "found pid: " << pid << endl;
	PVZ* pvz = new PVZ(pid);
	EventHandler e(pvz);
	Creater::AsmInit();
	read();
	srand(1024);
	e.RegisterPlantPlantEvent(onPlant);
	e.RegisterLevelWaveEvent(onWave);
	e.RegisterZombieSpawnEvent(onSpawn);
	Utils::SetPlantCost(PlantType::Peashooter, 225);
	Utils::SetPlantCost(PlantType::Cabbagepult, 250);
	Utils::SetPlantCost(PlantType::Doomshroon, 350);
	Utils::SetPlantCooldown(PlantType::Doomshroon, 1500);
	while (1)
	{
		int n = GetAllZombies(pvz);
		cerr << "now has " << n << " wave " <<pvz->RefreshedWave<<endl;
		if (n != 0&&pvz->RefreshedWave != 0)
			if(z[pvz->RefreshedWave].size() / 2 < n)
			pvz->NextWaveCountdown = 1800;
		cerr << pvz->NextWaveCountdown << endl;
		e.Run();
		Sleep(50);
	}
	delete pvz;
	return 0;
}
