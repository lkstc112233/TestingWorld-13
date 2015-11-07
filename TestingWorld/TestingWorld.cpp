// TestingWorld.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <string>

#include "utilities.h"
#include "Dot.h"
#include "Position.h"
#include "DirectPosition.h"
#include "RelativePosition.h"
#include "Entity.h"
#include "Weapon.h"
#include "Character.h"
#include "DotModule.h"
#include "DotProperty.h"

//#define OUTPUT_TO_FILE
#define OUTPUT_TO_GRAPH

#ifdef OUTPUT_TO_GRAPH
extern "C"
{
#include "D:\Programs\Downloaded Files\libpng-1.5.23\png.h"
}
#include <sstream>
#include <cstdio>

#endif

#ifdef OUTPUT_TO_FILE
#include <fstream>
std::ofstream cout("result.txt");
#else
using std::cout;
#endif
using std::endl;

void dot_pos_unittest()
{
	shared_ptr<CDirectPosition> directDotPos(new CDirectPosition);
	directDotPos->setPos(1, 1);

	shared_ptr<CDirectPosition> dPos2(new CDirectPosition);
	dPos2->setPos(3, 3);

	shared_ptr<CRelativePosition> rPos(new CRelativePosition);
	rPos->setRelativePos(dPos2);
	rPos->setDxDy(2, 2);

	shared_ptr<CRelativePosition> relaPos2(new CRelativePosition);
	relaPos2->setRelativePos(rPos);
	relaPos2->setDxDy(1, -2);

	CDot dot1;
	dot1.setPosition(directDotPos);
	CDot dot2;
	dot2.setPosition(dPos2);
	CDot dot3;
	dot3.setPosition(rPos);
	CDot dot4;
	dot4.setPosition(relaPos2);

	auto outputInformations = [&dot1, &dot2, &dot3, &dot4]
	{
		cout << "dot1 and dot2 collide check result:" << dot1.CollideCheck(dot2) << endl;
		cout << "dot2 and dot3 collide check result:" << dot2.CollideCheck(dot3) << endl;
		cout << "dot1 and dot3 collide check result:" << dot1.CollideCheck(dot3) << endl;
		cout << "dot1 and dot4 collide check result:" << dot1.CollideCheck(dot4) << endl;
		cout << "dot2 and dot4 collide check result:" << dot2.CollideCheck(dot4) << endl;
		cout << "dot3 and dot4 collide check result:" << dot3.CollideCheck(dot4) << endl;
		cout << "dot1's pos are:x=" << dot1.getPosition().getX() << ",y=" << dot1.getPosition().getY() << endl;
		cout << "dot2's pos are:x=" << dot2.getPosition().getX() << ",y=" << dot2.getPosition().getY() << endl;
		cout << "dot3's pos are:x=" << dot3.getPosition().getX() << ",y=" << dot3.getPosition().getY() << endl;
		cout << "dot4's pos are:x=" << dot4.getPosition().getX() << ",y=" << dot4.getPosition().getY() << endl;
	};

	outputInformations();
	cout << "Now turn dot2 with PI/2" << endl;
	dPos2->turn(PI / 2);
	outputInformations();
	cout << "Now turn dot2 with PI/2" << endl;
	dPos2->turn(PI / 2);
	outputInformations();
	cout << "Now reset dot3 with 0.9, 0.9" << endl;
	rPos->setDxDy(0.9, 0.9);
	outputInformations();
	cout << "Now turn dot2 with PI/2" << endl;
	dPos2->turn(PI / 2);
	outputInformations();

}

void entity_entity_collide_unittest()
{
	int entityCounter = 0;
#ifdef OUTPUT_TO_GRAPH
#pragma warning(disable:4244)
#pragma warning(disable:4101)
	auto printEntity = [&entityCounter](CEntity& entity, std::string str = "")
	{
		std::string filename = "Frame No.";
		filename = filename + ConvertToString(++entityCounter) + ".png";
		FILE *fp;
		png_structp png_ptr;
		png_infop info_ptr;
		png_colorp palette;

		/* ����Ҫд����ļ� */
		fopen_s(&fp,filename.c_str(), "wb");
		//if (fp == NULL)
		//	return (ERROR);

		/* ��������ʼ�� png_struct ��������Ĵ����������������ʹ��Ĭ
		* �ϵ� stderr �� longjump() ����������Խ��������������Ϊ NULL��
		* ��ʹ�ö�̬���ӿ������£�����Ҳ���⺯����汾�Ƿ����ڱ���ʱ
		* ʹ�õİ汾�Ƿ���ݡ�����Ҫ��
		*/
		png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

		if (png_ptr == NULL)
		{
			fclose(fp);
			return;//(ERROR);
		}

		/* �����ڴ沢��ʼ��ͼ����Ϣ���ݡ�����Ҫ��*/
		info_ptr = png_create_info_struct(png_ptr);
		if (info_ptr == NULL)
		{
			fclose(fp);
			png_destroy_write_struct(&png_ptr, NULL);
			return;//(ERROR);
		}

		/* ���ô�����������ڵ��� png_create_write_struct() ʱû
		* �����ô�����������ô��δ����Ǳ���д�ġ�*/
		if (setjmp(png_jmpbuf(png_ptr)))
		{
			/* ��������ܵ������ˣ���ôд���ļ�ʱ���������� */
			fclose(fp);
			png_destroy_write_struct(&png_ptr, &info_ptr);
			return; //(ERROR);
		}

		/* ����������ƣ������ʹ�õ��� C �ı�׼ I/O �� */
		png_init_io(png_ptr, fp);

		/* ����һ�ָ��ӵ����� */

		/* �����裩����������ͼ�����Ϣ����ȡ��߶ȵ������� 2^31��
		* bit_depth ȡֵ������ 1��2��4��8 ���� 16, ���ǿ��õ�ֵҲ������ color_type��
		* color_type ��ѡֵ�У� PNG_COLOR_TYPE_GRAY��PNG_COLOR_TYPE_GRAY_ALPHA��
		* PNG_COLOR_TYPE_PALETTE��PNG_COLOR_TYPE_RGB��PNG_COLOR_TYPE_RGB_ALPHA��
		* interlace ������ PNG_INTERLACE_NONE �� PNG_INTERLACE_ADAM7,
		* �� compression_type �� filter_type Ŀǰ������ PNG_COMPRESSION_TYPE_BASE
		* �� and PNG_FILTER_TYPE_BASE��
		*/
		png_set_IHDR(png_ptr, info_ptr, 100, 100, 8, PNG_COLOR_TYPE_RGB_ALPHA,
			PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

		/* д���ļ�ͷ����Ϣ�����裩 */
		png_write_info(png_ptr, info_ptr);

		png_uint_32 k, height=100, width=100;

		/* �����ʾ�������У�"image" ��һ��һά���ֽ����飨ÿ��Ԫ��ռһ���ֽڿռ䣩 */
		static png_byte image[100 * 100 * 4] = { 0 };

		for (auto dot : entity.getModule().getStorage())
		{
			int y = dot->getPosition().getX() + 50;
			int x = -dot->getPosition().getY() + 50;
			image[100 * x * 4 + y * 4 + 3] = 0xff;
			if (dot->getProperty().getDotType() == PT_DAMAGE)
				image[100 * x * 4 + y * 4] = 0xff;
			else
			{
				double factor = (dot->getProperty().getHealthPoint() > 0 ? dot->getProperty().getHealthPoint()*1.0 : 0) / dot->getProperty().getMaxHealthPoint();
				image[100 * x * 4 + y * 4 + 1] = 0xff * factor;
				image[100 * x * 4 + y * 4 + 2] = 0xff;
			}
		}

//		for (int x = 20; x < 150; ++x)
//			for (int y = 20; y < 40; ++y)
//			{
//				image[200 * x*4 + y*4 + 3] = 0xff;
//				image[200 * x*4 + y*4] = 0xff;
//			}

		png_bytep row_pointers[200];

		if (height > PNG_UINT_32_MAX / (sizeof(png_bytep)))
			png_error(png_ptr, "Image is too tall to process in memory");

		/* ����Щ������ָ��ָ����� "image" �ֽ������ж�Ӧ��λ�ã�����ָ��ÿ�����ص���ʼ�� */
		for (k = 0; k < height; k++)
			row_pointers[k] = image + k*width*4;

		if (str.compare("Jack") == 0)
		{
			/* һ�ε��þͽ�����ͼ��д���ļ� */
			png_write_image(png_ptr, row_pointers);
			/* �����������������д���ļ����ಿ�� */
			png_write_end(png_ptr, info_ptr);
			/* д��������ͷ��ѷ�����ڴ� */
			png_destroy_write_struct(&png_ptr, &info_ptr);
		}
		/* �ر��ļ� */
		fclose(fp);

		/* That's it */

		if (str.compare("Jack") == 0)
			for (int i = 0; i < 100 * 100 * 4; ++i)
				image[i] = 0;

		return;
	};
#pragma warning(default:4244)
#pragma warning(default:4101)
#else
	auto printEntity = [&entityCounter](CEntity& entity, std::string str = "")
	{
		if (str != "")
			cout << "----Now printing states in Entity " << str << endl;
		else
			cout << "----Now printing states in Entity No." << ++entityCounter << endl;
		int counter = 0;
		for (auto dot : entity.getModule().getStorage())
		{
			cout << "\tDot No." << ++counter << "Status:" << endl;
			cout << "\t\tx=" << dot->getPosition().getX() << ", y=" << dot->getPosition().getY() << endl;
			cout << "\t\tHP=" << dot->getProperty().getHealthPoint() << "/" << dot->getProperty().getMaxHealthPoint() << endl;
		}
	};
#endif

	//Create a weapon
	shared_ptr<CDotModule> weaponModule(new CDotModule);
	auto insertDotToWeapon = [weaponModule](shared_ptr<CPosition> pos)
	{
		shared_ptr<CDot> dot(new CDot);
		dot->setPosition(pos);
		dot->formProperty(PT_DAMAGE);
		weaponModule->addDot(dot);
	};

	shared_ptr<CDirectPosition> ancher(new CDirectPosition);
	ancher->setPos(0, 0);
	insertDotToWeapon(ancher);

	for (int i = 0; i < 4; i++)
	{
		shared_ptr<CRelativePosition> body(new CRelativePosition);
		body->setRelativePos(ancher);
		body->setDxDy(0, i + 1);
		insertDotToWeapon(body);
	}
	for (int i = 0; i < 5; i++)
	{
		shared_ptr<CRelativePosition> body(new CRelativePosition);
		body->setRelativePos(ancher);
		body->setDxDy(i - 2, 5);
		insertDotToWeapon(body);
	}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
		{
			shared_ptr<CRelativePosition> body(new CRelativePosition);
			body->setRelativePos(ancher);
			body->setDxDy(i - 1, j + 6);
			insertDotToWeapon(body);
		}
	shared_ptr<CWeapon> weapon(new CWeapon);
	weapon->setModule(weaponModule);

	//Create another weapon
	shared_ptr<CDotModule> weaponModule2(new CDotModule);
	auto insertDotToWeapon2 = [weaponModule2](shared_ptr<CPosition> pos)
	{
		shared_ptr<CDot> dot(new CDot);
		dot->setPosition(pos);
		dot->formProperty(PT_DAMAGE);
		weaponModule2->addDot(dot);
	};

	shared_ptr<CDirectPosition> ancher2(new CDirectPosition);
	ancher2->setPos(0, 0);
	insertDotToWeapon2(ancher2);

	for (int i = 0; i < 15; i++)
	{
		shared_ptr<CRelativePosition> body(new CRelativePosition);
		body->setRelativePos(ancher2);
		body->setDxDy(0, i + 1);
		insertDotToWeapon2(body);
	}
	shared_ptr<CWeapon> weapon2(new CWeapon);
	weapon2->setModule(weaponModule2);

	//Create a Jack:)
	shared_ptr<CDotModule> jackModule(new CDotModule);
	auto insertDotToJack = [jackModule](shared_ptr<CPosition> pos)
	{
		shared_ptr<CDot> dot(new CDot);
		dot->setPosition(pos);
		dot->formProperty(PT_GRASS);
		jackModule->addDot(dot);
	};

	shared_ptr<CDirectPosition> directPos(new CDirectPosition);
	directPos->setPos(5, 0);
	insertDotToJack(directPos);

	shared_ptr<CRelativePosition> body(new CRelativePosition);
	body->setRelativePos(directPos);
	body->setDxDy(0, 1);
	insertDotToJack(body);


	for (int i = 0; i < 2; i++)
	{
		shared_ptr<CRelativePosition> body(new CRelativePosition);
		body->setRelativePos(directPos);
		body->setDxDy(3, i);
		insertDotToJack(body);
	}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			shared_ptr<CRelativePosition> body(new CRelativePosition);
			body->setRelativePos(directPos);
			body->setDxDy(i, j + 2);
			insertDotToJack(body);
		}
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			shared_ptr<CRelativePosition> body(new CRelativePosition);
			body->setRelativePos(directPos);
			body->setDxDy(i + 1, j + 6);
			insertDotToJack(body);
		}
	shared_ptr<CCharacter> jack(new CCharacter);
	jack->setModule(jackModule);

	printEntity(*weapon, "Weapon2");
	printEntity(*jack, "Jack");

	for (int i = 0; i < 18; ++i)
	{
		ancher->turn(PI / 36);
		weapon->getModule().interactWith(jack->getModule());
		cout << endl << "After frame No." << i << ", Result are:" << endl << endl;
		printEntity(*weapon, "Weapon");
		printEntity(*jack, "Jack");
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	//dot_pos_unittest();
	entity_entity_collide_unittest();
	system("PAUSE");
	return 0;
}

