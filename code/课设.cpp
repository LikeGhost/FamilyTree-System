#include<stdio.h>
#include<iostream>
#include<string>
#include<cstring>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#include<new>
using namespace std;
struct Man //��Ա��Ϣ
{
	string name;//����
	char sex;//�Ա�
	int age;//����
	Man* spouse = NULL;//��ż
}*member[1000];
struct Member {
	Man* man = NULL;
	Member* father = NULL, * child = NULL, * brother = NULL,*pre=NULL;
	//�������ڵ�
};

template<typename Tname>
class QUE {
public:
	void push(Tname d) {
		nodeQ* pushdata = new nodeQ;
		pushdata->data = d;
		pushdata->next = NULL;
		rear->next = pushdata;
		rear = pushdata;
		length++;
	}
	Tname front() {
		nodeQ* Delete = New->next;
		Tname Re;
		if (Delete == rear)rear = New;
		New->next = Delete->next;
		Re = Delete->data;
		length--;
		return Re;
	}
	bool isempty() {
		if (length == 0)return 1;
		else return 0;
	}
	int l() {
		return length;
	}
	QUE() {
		New = new nodeQ;
		rear = New;
	}
private:
	struct nodeQ {
		Tname data;
		nodeQ* next;
	};
	nodeQ* New = new nodeQ, * rear;
	int length = 0;
};
int count = 0;
string F;
bool iss = true;
void SetUp() {
	printf("\n\n             **       *       **  ******  *       ****    ****       *       *       ******\n");
	printf("              **     ***     **   *       *      *       *    *     ***     ***      *     \n");
	printf("               **   ** **   **    *****   *      *       *    *    ** **   ** **     ***** \n");
	printf("                ** **   ** **     *       *      *       *    *   **   ** **   **    *     \n");
	printf("                 ***     ***      *       *      *       *    *  **     ***     **   *     \n");
	printf("                  *       *       ******  ******  ****    ****  **       *       **  ******\n");
	//��ӭ����
	printf("\n\n\n%*c** �� �� �� ϵ �� ѯ ϵ ͳ **\n", 30, ' ');
	printf("\n\n%*c���ܲ˵�����:", 30, ' ');
	printf("\n\n%*c1.�½�һ�������ϵ", 34, ' ');
	printf("\n\n%*c2.��һ�������ϵ", 34, ' ');
	printf("\n\n%*c3.�޸ļ����Ա��Ϣ", 34, ' ');
	printf("\n\n%*c4.��ѯ�����Ա��Ϣ", 34, ' ');
	printf("\n\n%*c5.�˳�ϵͳ", 34, ' ');
	printf("\n\n%*c������˵���Ž���ѡ��", 30, ' ');
}
Member* Creat_Tree() //����
{
	Member* FT = new Member;
	Member* father;
	QUE<Member*>Q;//��������
	int i = 0;
	FT->man = member[i++];
	Q.push(FT);
	while (member[i]->name != "#") {
		while (member[i]->name != "@") {
			Member* New = new Member;//�½���Ա�ڵ�
			New->man = member[i];
			New->father = father;
			New->brother = father->child;
			if(father->child)
				father->child->pre = New;
			father->child = New;
			Q.push(New);//���
			i++;
		}
		father = Q.front();
		i++;
	}
	return FT;
}
Member* Open(string filename = "")///���ļ�
{
	system("cls");//����
	FILE* fp;
	char ch[100], od;
	Member* ret = NULL;
	memset(member, 0, sizeof(Man*) * 1000);
	if (filename == "") {
		cout << "����������ϵ�ļ�����";
		scanf("%s", ch);
		cout << endl;
		filename = ch;
		filename = filename + ".txt";
	}
	fp = fopen(filename.c_str(), "r+");
	if (!fp) {
		cout << "��ʱû�д˼����ϵ�ļ���" << endl;
		Sleep(700);
		return NULL;
	}
	string n;
	char name[100], sex;
	int age;
	bool flag = true;
	for (int i = 0;;) {
		if (flag)
			fscanf(fp, "%s", name);
		flag = true;
		Man* New = new Man;//�����ڵ�
		New->name = name;
		if (New->name == "#") {
			member[i++] = New;
			break;
		}
		else if (New->name == "@") {
			member[i++] = New;
		}
		else if (New->name != "@") {//������Ϣ
			fscanf(fp, "%c", &sex);
			fscanf(fp, "%c", &sex);
			New->sex = sex;
			fscanf(fp, "%d", &age);
			New->age = age;
			fscanf(fp, "%s", name);
			n = name;
			if (n == "��ż��") {//������ż��Ϣ
				New->spouse = new Man;
				fscanf(fp, "%s", name);
				New->spouse->name = name;
				fscanf(fp, "%c", &sex);
				fscanf(fp, "%c", &sex);
				New->spouse->sex = sex;
				fscanf(fp, "%d", &age);
				New->spouse->age = age;
			}
			else {
				flag = 0;
			}
			member[i++] = New;
		}
	}
	ret = Creat_Tree();//���ý�������
	F = filename;
	cout << "�򿪳ɹ���" << endl;
	Sleep(700);
	return ret;
}
Member* Creat(Member* FT) {//���������ϵ�����浽�ļ�
	system("cls");//����
	string filename;
	FILE* fp;
	char ch[100], od;
	memset(member, 0, sizeof(Man*) * 1000);
	Member* ret = NULL;
	cout << "������������ϣ�";
	scanf("%s", ch);
	cout << endl;
	filename = ch;
	filename = filename + ".txt";
	fp = fopen(filename.c_str(), "r+");
	if (fp) {
		fclose(fp);
		printf("%s�ϼ����ϵ�Ѵ��ڣ���Y�򿪣�R�ؽ�,Q�������˵���\n\n", ch);
		od = getch();
		if (od == 'y' || od == 'Y')
		{
			ret = Open(filename);//���ô򿪺���
			return ret;
		}

	}
	if (!fp || od == 'R' || od == 'r') {
		fp = fopen(filename.c_str(), "w+");
		cout << "�밴��������㣬ÿ�������Ϣռһ��\n\n";
		cout << "�ֵ���������ԡ�@��Ϊ��־��������־Ϊ��#��������ż���롰N�������롰!���������˵�\n\n";


		for (int i = 0;;) {
			string n;
			char name[100], sex;
			int age;
			cout << "������";
			scanf("%s", name);
			Man* New = new Man;
			New->name = name;
			if (New->name == "!"|| New->name == "��") {//�������˵�
				return NULL;
			}
			if (New->name == "#") {//�������
				member[i++] = New;
				fprintf(fp, "#\n");
				break;
			}
			else if (New->name == "@") {//�ֵ��������
				fprintf(fp, "@\n");
				member[i++] = New;
			}
			else if (New->name != "@") {
				cout << "�Ա�";
				while (1) {
					sex = getche();
					printf("\n");
					if (sex != 'F' && sex != 'M') {//�Ա��������
						printf("��������ȷ���Ա�F/M����");
					}
					else  break;
				}
				New->sex = sex;
				cout << "���䣺";
				scanf("%d", &age);
				New->age = age;
				cout << "��ż��";
				scanf("%s", name);
				n = name;
				if (n != "N") {//��ż
					New->spouse = new Man;
					New->spouse->name = n;
					cout << "�Ա�";
					while (1) {
						sex = getche();
						cout << endl;
						if (sex != 'F' && sex != 'M') {//�Ա��������
							cout << "��������ȷ���Ա�F/M����";
						}
						else  break;
					}
					New->spouse->sex = sex;
					cout<<"���䣺";
					scanf("%d", &age);
					New->spouse->age = age;
				}
				member[i++] = New;
				fprintf(fp, "%6s %c %d ", New->name.c_str(), New->sex, New->age);
				if (New->spouse) {
					fprintf(fp, "��ż�� %6s %c %d", New->spouse->name.c_str(), New->spouse->sex, New->spouse->age);
				}
				fprintf(fp, "\n");
			}
		}
		ret = Creat_Tree();//���ý�������
		F = filename;
		
		fclose(fp);
		cout << "�����ɹ���\n";
		getch();
		Sleep(700);
		return ret;
	}
	else if (od == 'q' || od == 'Q') {
		return NULL;
	}

}
Member* Search(Member* FT, string name)//������
{
	if (!FT)return NULL;
	Member* ret = NULL;
	if (FT->man->name == name) {
		iss = false;
		return FT;
	}
	else if (FT->man->spouse && FT->man->spouse->name == name) {
		iss = true;
		return FT;
	}
	ret = Search(FT->child, name);
	if (!ret)
		ret = Search(FT->brother, name);
	return ret;
}
string GpPrint(Man *gp, Man* fa)//үү�����⹫����
{
	int x=1, y=1;
	string ret;
	const char* gpre[2][20] = { {"үү","����"},{"�⹫","����"} };
	if (gp->sex == 'M')y = 0;
	if (fa->sex == 'M')x = 0;
	ret = gpre[x][y];
	return ret;
}
string FaPrint(Man* fa) //����ĸ��
{
	if (fa->sex == 'M')return "����";
	else return"ĸ��";
}
string FabPrint(Man* fab,Man* fa) //��ϵ��ͬϵ
{
	int x = 1, y = 2;
	string ret;
	const char* fare[2][20] = { {"����","�常","�ù�"},{"�˾�","�˾�","����"} };
	if (fab == fa)return "��ͬ";
	if (fa->sex == 'M')x = 0;
	if (fab->sex == 'M') {
		if (x == 1) {
			if (fab->age >= fa->age)y = 0;
			else y = 1;
		}
		else y = 0;
	}
	ret = fare[x][y];
	return ret;
}
string BroPrint(Man* bro, Man* me)//ͬϵ
{
	int x = 1, y = 1;
	string ret;
	const char* brore[2][20] = { {"���","���"},{"�ܵ�","����"} };
	if (bro->age > me->age)x = 0;
	if (bro->sex == 'M')y = 0;
	ret = brore[x][y];
	return ret;
}
string GsPrint(Man* gs, Man* so) //��ϵ
{
	int x = 1, y = 1;
	string ret;
	const char* gsre[2][20] = { {"����","��Ů"},{"����","����Ů"} };
	if (gs->sex == 'M')y = 0;
	if (so->sex == 'M')x = 0;
	ret = gsre[x][y];
	return ret;

}
void Relation(Member* FT) {
	system("cls");//����
	Member* r;
	string name;
	char n[100];
	cout<<"��ѯ�ߵ����֣�";
	scanf("%s", n);
	cout << endl;
	name = n;//����string����
	if (!FT) {
		cout << "���Ƚ�����������\n";
		Sleep(700);
	}
	r = Search(FT, name);
	if (!r) {//û���ҵ�
		cout<<"����δ�ڱ�����������ʾ��\n";
		Sleep(700);
		return;
	}
	Member* gp, * fa, * so, * gs,*fab,*bro;
	QUE<Member*>bf, sf, gg, jj, ym,ge,ji,di,me,ez,ne,sz,sn,ws,wn;
	

	while (1) {
		system("cls");//����
		printf("��ѯ�ߵ����֣�%s",name.c_str());
		printf("\n\n%*c1.��ѯ����", 32, ' ');
		printf("\n\n%*c2.��ѯүϵ", 32, ' ');
		printf("\n\n%*c3.��ѯ��ϵ", 32, ' ');
		printf("\n\n%*c4.��ѯ�ֵܽ���", 32, ' ');
		printf("\n\n%*c5.��ѯ��Ů", 32, ' ');
		printf("\n\n%*c6.��ѯ��ϵ", 32, ' ');
		printf("\n\n%*c0.�˳���ѯ", 32, ' ');
		printf("\n\n%*c������˵���Ž���ѡ��", 30, ' ');
		//���Ҳ˵�
		char ch;
		int order;
		ch = getch();
		cout << endl << endl;
		order = ch - '0';
		switch (order)
		{
		case 1:
			printf("%s��������%s", name.c_str(), FT->man->name.c_str());//ֱ�ӷ��ظ��ڵ�
			cout << "\n\n������������ϼ��˵�";
			ch = getch();
			break;
		case 2:
			if (!r->father) {//��ϵ��������үϵ������
				printf("%s��үϵδ�ڱ�����������ʾ\n\n",name.c_str());
				cout << "\n\n������������ϼ��˵�";
				ch = getch();
				break;
			}
			if (!r->father->father) {//үϵ������
				printf("%s��үϵδ�ڱ�����������ʾ\n\n",name.c_str());
				cout << "\n\n������������ϼ��˵�";
				ch = getch();
				break;
			}
			gp = r->father->father;
			fa = r->father;
			printf("\n%s��%s��%s",name.c_str(),GpPrint(gp->man,fa->man).c_str(),gp->man->name.c_str());
			if(r->father->father->man->spouse)
				printf("\n%s��%s��%s", name.c_str(), GpPrint(gp->man->spouse, fa->man).c_str(), gp->man->spouse->name.c_str());
			cout << "\n\n������������ϼ��˵�";
			ch = getch();
			break;
		case 3:
			if (!r->father) {//��ϵ������
				printf("%s�ĸ�ϵδ�ڱ�����������ʾ\n\n", name.c_str());
				cout << "\n\n������������ϼ��˵�";
				ch = getch();
				break;
			}
			else {
				fa = r->father, fab = fa;

				printf("\n%s��%s��%s", name.c_str(), FaPrint(fa->man).c_str(), fa->man->name.c_str());
				if (fa->man->spouse)
					printf("\n%s��%s��%s", name.c_str(), FaPrint(fa->man->spouse).c_str(), fa->man->spouse->name.c_str());
				for (; fab->pre; fab = fab->pre);
				for (; fab; fab = fab->brother) {
					if (FabPrint(fab->man, fa->man) == "����")bf.push(fab);
					if (FabPrint(fab->man, fa->man) == "�常")sf.push(fab);
					if (FabPrint(fab->man, fa->man) == "�ù�")gg.push(fab);
					if (FabPrint(fab->man, fa->man) == "�˾�")jj.push(fab);
					if (FabPrint(fab->man, fa->man) == "����")ym.push(fab);
				}
				if (!bf.isempty())printf("\n%s�Ĳ�����", name.c_str());
				while (!bf.isempty())printf("%s ", bf.front()->man->name.c_str());
				if (!sf.isempty())printf("\n%s���常��", name.c_str());
				while (!sf.isempty())printf("%s ", sf.front()->man->name.c_str());
				if (!gg.isempty())printf("\n%s�Ĺù���", name.c_str());
				while (!gg.isempty())printf("%s ", gg.front()->man->name.c_str());
				if (!jj.isempty())printf("\n%s�ľ˾���", name.c_str());
				while (!jj.isempty())printf("%s ", jj.front()->man->name.c_str());
				if (!ym.isempty())printf("\n%s��������", name.c_str());
				while (!ym.isempty())printf("%s ", ym.front()->man->name.c_str());
			}
			cout << "\n\n������������ϼ��˵�";
			ch = getch();
			break;
		case 4:
			bro = r;
			for (; bro->pre; bro = bro->pre);
			if (r == bro) {//ͬϵ������
				printf("%sû���ֵܽ���\n",name.c_str());
				printf("\n\n������������ϼ��˵�");
				ch = getch();
				break;
			}
			else {
				for (; bro; bro = bro->brother) {
					if (BroPrint(bro->man, r->man) == "���")ge.push(bro);
					if (BroPrint(bro->man, r->man) == "���")ji.push(bro);
					if (BroPrint(bro->man, r->man) == "�ܵ�")di.push(bro);
					if (BroPrint(bro->man, r->man) == "����")me.push(bro);
				}
				if (!ge.isempty())printf("\n%s�ĸ����", name.c_str());
				while (!ge.isempty())printf("%s ", ge.front()->man->name.c_str());
				if (!ji.isempty())printf("\n%s�Ľ����", name.c_str());
				while (!ji.isempty())printf("%s ", ji.front()->man->name.c_str());
				if (!di.isempty())printf("\n%s�ĵܵ���", name.c_str());
				while (!di.isempty())printf("%s ", di.front()->man->name.c_str());
				if (!me.isempty())printf("\n%s��������", name.c_str());
				while (!me.isempty())printf("%s ", me.front()->man->name.c_str());
			}
			cout << "\n\n������������ϼ��˵�";
			ch = getch();
			break;
		case 5:
			if (!r->child) {//��ϵ������
				printf("%sû����Ů",name.c_str());
				cout << "\n\n������������ϼ��˵�";
				ch = getch();
				break;
			}
			so = r->child;
			for (;so;so=so->brother) {
				if (so->man->sex == 'M')ez.push(so);
				else ne.push(so);
			}
			if (!ez.isempty())printf("\n%s��", name.c_str());
			while (!ez.isempty()) {
				so = ez.front();
				printf("\n������%s",so->man->name.c_str());
				if (so->man->spouse)
					printf("����ϱ��%s", so->man->spouse->name.c_str());
			
			}
			if (!ne.isempty())printf("\n%s��", name.c_str());
			while (!ne.isempty()) {
				so = ne.front();
				printf("\nŮ����%s", so->man->name.c_str());
				if (so->man->spouse)
					printf("��Ů����%s", so->man->spouse->name.c_str());

			}
			cout << "\n\n������������ϼ��˵�";
			ch = getch();
			break;
		case 6:
			if (!r->child) {//��ϵ����������ϵ������
				printf("%s����ϵδ�ڱ�����������ʾ\n\n", name.c_str());
				cout << "\n\n������������ϼ��˵�";
				ch = getch();
				break;
			}
			so = r->child;
			for(;so;so=so->brother){
				if (so->child)break;
			}
			if (!so) {//��ϵ������
				printf("%s����ϵδ�ڱ�����������ʾ\n\n", name.c_str());
				cout << "\n\n������������ϼ��˵�";
				ch = getch();
				break;
			}
			so = r->child;
			for (; so; so = so->brother) {
				gs = so->child;
				for (; gs; gs = gs->brother) {
					if (GsPrint(gs->man, so->man) == "����")sz.push(gs);
					if (GsPrint(gs->man, so->man) == "��Ů")sn.push(gs);
					if (GsPrint(gs->man, so->man) == "����")ws.push(gs);
					if (GsPrint(gs->man, so->man) == "����Ů")wn.push(gs);
				}
			}
			if (!sz.isempty())printf("\n%s��������", name.c_str());
			while (!sz.isempty())printf("%s ", sz.front()->man->name.c_str());
			if (!sn.isempty())printf("\n%s����Ů��", name.c_str());
			while (!sn.isempty())printf("%s ", sn.front()->man->name.c_str());
			if (!ws.isempty())printf("\n%s��������", name.c_str());
			while (!ws.isempty())printf("%s ", ws.front()->man->name.c_str());
			if (!wn.isempty())printf("\n%s������Ů��", name.c_str());
			while (!wn.isempty())printf("%s ", wn.front()->man->name.c_str());
			cout << "\n\n������������ϼ��˵�";
			ch = getch();
			break;

		case 0:

			return;
		default:
			cout << "��������ȷ�Ĳ˵���ţ�";
			break;
		}
	}
}
void Change(Member* FT)//�޸ĳ�Ա��Ϣ
{
	system("cls");
	Member* r,*New,*T;
	Man* spouse,*child;
	string name;
	char n[100];
	int sign = 1;
	FILE* fp;
	QUE<Member*>Q;//��������
	cout<<"�޸��ߵ����֣�";
	scanf("%s", n);
	cout << endl;
	name = n;
	if (!FT) {//������������
		cout << "���Ƚ�����������\n";
		Sleep(700);
		return;
	}
	r = Search(FT, name);
	if (!r) {//�Ҳ���
		cout << "����δ�ڱ�����������ʾ��\n";
		Sleep(700);
		return;
	}
	else {
		while (1) {
			system("cls");//����
			printf("�޸��ߵ����֣�%s", name.c_str());
			printf("\n\n%*c1.�޸�", 32, ' ');
			printf("\n\n%*c2.ɾ��", 32, ' ');
			printf("\n\n%*c3.�����Ů", 32, ' ');
			printf("\n\n%*c4.�����ż", 32, ' ');
			printf("\n\n%*c0.�˳���ѯ", 32, ' ');
			printf("\n\n%*c������˵���Ž���ѡ��", 30, ' ');
			//�˵�
			char ch;
			int order;
			ch = getch();
			order = ch - '0';
			cout << endl << endl;
			switch (order)
			{
			case 1:
				cout << "������";
				scanf("%s", n);
				if (iss) r->man->spouse->name=n;
				else r->man->name=n;
				cout << "�Ա�";
				while (1) {
					if (iss)r->man->spouse->sex = getche();
					else r->man->sex = getche();
					cout << endl;
					if (r->man->sex != 'F' && r->man->sex != 'M' || r->man->spouse->sex != 'F' && r->man->spouse->sex != 'M') {
						cout << "��������ȷ���Ա�F/M����";
					}
					else  break;
				}
				cout << "���䣺";
				if (iss)scanf("%d", &r->man->spouse->age);
				else scanf("%d", &r->man->age);
				cout << "�޸ĳɹ���";
				Sleep(700);
				break;
			case 2:
				if (iss) {
					delete r->man->spouse;
					r->man->spouse = NULL;
					cout << "ɾ���ɹ���";
					Sleep(700);
				}
				else {
					cout << "�˳�Ա��¼��ĺ����һ��ɾ�����Ƿ�ɾ���ó�Ա����Y/N)";
					ch = getch();
					if (ch == 'Y' || ch == 'y') {
						if (r->brother)
							r->brother->pre = r->pre;
						r->pre->brother = r->brother;
						delete r;
						cout << "ɾ���ɹ���";
						Sleep(700);
					}
				}
				fp = fopen(F.c_str(), "w+");
				fprintf(fp, "%6s %c %d ", FT->man->name.c_str(), FT->man->sex, FT->man->age);
				if (FT->man->spouse) {
					fprintf(fp, "��ż�� %6s %c %d", FT->man->spouse->name.c_str(), FT->man->spouse->sex, FT->man->spouse->age);
				}
				fprintf(fp, "\n");
				fprintf(fp, "@\n");
				Q.push(FT);
				 sign = 1;
				while (sign || !Q.isempty()) {
					New = Q.front();
					T = New->child;
					if (!T)continue;
					for (; T; T = T->brother) {
						fprintf(fp, "%6s %c %d ", T->man->name.c_str(), T->man->sex, T->man->age);
						if (T->man->spouse) {
							fprintf(fp, "��ż�� %6s %c %d", T->man->spouse->name.c_str(), T->man->spouse->sex, T->man->spouse->age);
						}
						fprintf(fp, "\n");
						Q.push(T);
					}
					fprintf(fp, "@\n");
					sign = 0;
				}
				fprintf(fp, "#\n");
				fclose(fp);
				return;
			case 3:
				child = new Man;
				New = new Member;
				cout << "������";
				scanf("%s", n);
				child->name = n;
				cout << "�Ա�";
				while (1) {
					child->sex = getche();
					cout << endl;
					if (child->sex != 'F' && child->sex != 'M') {
						cout << "��������ȷ���Ա�F/M����";
					}
					else  break;
				}
				cout << "���䣺";
				scanf("%d", &child->age);
				New->man = child;
				New->father = r;
				New->brother = r->child;
				if (r->child)
					r->child->pre = New;
				r->child = New;
				cout << "��ӳɹ���";
				Sleep(700);
				break;
			case 4:
				spouse = new Man;
				if (r->man->spouse) {
					cout << "�˳�Ա������ż�Ƿ��޸ģ�(Y/N��";
					ch = getch();
					cout << endl << endl;
					if (ch != 'y' && ch != 'Y')break;
				}
				cout << "������";
				scanf("%s",n);
				spouse->name = n;
				cout << "�Ա�";
				while (1) {
					spouse->sex = getche();
					cout << endl;
					if (spouse->sex != 'F' && spouse->sex != 'M') {
						cout << "��������ȷ���Ա�F/M����";
					}
					else  break;
				}
				cout << "���䣺";
				scanf("%d", &spouse->age);
				r->man->spouse = spouse;
				cout << "��ӳɹ���";
				Sleep(700);
				break;
			case 0:
				fp = fopen(F.c_str(), "w+");
				fprintf(fp, "%6s %c %d ", FT->man->name.c_str(), FT->man->sex, FT->man->age);
				if (FT->man->spouse) {
					fprintf(fp, "��ż�� %6s %c %d", FT->man->spouse->name.c_str(), FT->man->spouse->sex, FT->man->spouse->age);
				}
				fprintf(fp, "\n");
				fprintf(fp, "@\n");
				Q.push(FT);
				 sign = 1;
				while (sign || !Q.isempty()) {
					New = Q.front();
					T = New->child;
					if (!T)continue;
					for (; T; T = T->brother) {
						fprintf(fp, "%6s %c %d ", T->man->name.c_str(), T->man->sex, T->man->age);
						if (T->man->spouse) {
							fprintf(fp, "��ż�� %6s %c %d", T->man->spouse->name.c_str(), T->man->spouse->sex, T->man->spouse->age);
						}
						fprintf(fp, "\n");
						Q.push(T);
					}
					fprintf(fp, "@\n");
					sign = 0;
				}
				fprintf(fp, "#\n");
				fclose(fp);
				return;
			}
		}
	}
}
int main() {
	char ch;
	Member* FT = NULL;
	while (1) {
		system("cls");
		SetUp();
		ch = getche();
		int order = ch - '0';
		switch (order)
		{
		case 1:
			FT=Creat(FT);
			break;
		case 2:
			FT = Open();
			break;
		case 3:
			Change(FT);
			break;
		case 4:
			Relation(FT);
			break;
		case 5:
			return 0;
		default:
			printf("\n\n%*c��������ȷ�Ĳ˵���ţ�", 30, ' ');
			Sleep(700);
			break;
		}
	}
}