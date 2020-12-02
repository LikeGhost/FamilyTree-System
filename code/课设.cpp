#include<stdio.h>
#include<iostream>
#include<string>
#include<cstring>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#include<new>
using namespace std;
struct Man //成员信息
{
	string name;//姓名
	char sex;//性别
	int age;//年龄
	Man* spouse = NULL;//配偶
}*member[1000];
struct Member {
	Man* man = NULL;
	Member* father = NULL, * child = NULL, * brother = NULL,*pre=NULL;
	//三叉链节点
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
	//欢迎界面
	printf("\n\n\n%*c** 家 族 关 系 查 询 系 统 **\n", 30, ' ');
	printf("\n\n%*c功能菜单如下:", 30, ' ');
	printf("\n\n%*c1.新建一个家族关系", 34, ' ');
	printf("\n\n%*c2.打开一个家族关系", 34, ' ');
	printf("\n\n%*c3.修改家族成员信息", 34, ' ');
	printf("\n\n%*c4.查询家族成员信息", 34, ' ');
	printf("\n\n%*c5.退出系统", 34, ' ');
	printf("\n\n%*c请输入菜单编号进行选择：", 30, ' ');
}
Member* Creat_Tree() //建树
{
	Member* FT = new Member;
	Member* father;
	QUE<Member*>Q;//调用链队
	int i = 0;
	FT->man = member[i++];
	Q.push(FT);
	while (member[i]->name != "#") {
		while (member[i]->name != "@") {
			Member* New = new Member;//新建成员节点
			New->man = member[i];
			New->father = father;
			New->brother = father->child;
			if(father->child)
				father->child->pre = New;
			father->child = New;
			Q.push(New);//入队
			i++;
		}
		father = Q.front();
		i++;
	}
	return FT;
}
Member* Open(string filename = "")///打开文件
{
	system("cls");//清屏
	FILE* fp;
	char ch[100], od;
	Member* ret = NULL;
	memset(member, 0, sizeof(Man*) * 1000);
	if (filename == "") {
		cout << "请输入家族关系文件名：";
		scanf("%s", ch);
		cout << endl;
		filename = ch;
		filename = filename + ".txt";
	}
	fp = fopen(filename.c_str(), "r+");
	if (!fp) {
		cout << "暂时没有此家族关系文件！" << endl;
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
		Man* New = new Man;//创建节点
		New->name = name;
		if (New->name == "#") {
			member[i++] = New;
			break;
		}
		else if (New->name == "@") {
			member[i++] = New;
		}
		else if (New->name != "@") {//复制信息
			fscanf(fp, "%c", &sex);
			fscanf(fp, "%c", &sex);
			New->sex = sex;
			fscanf(fp, "%d", &age);
			New->age = age;
			fscanf(fp, "%s", name);
			n = name;
			if (n == "配偶：") {//复制配偶信息
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
	ret = Creat_Tree();//调用建树函数
	F = filename;
	cout << "打开成功！" << endl;
	Sleep(700);
	return ret;
}
Member* Creat(Member* FT) {//创建家族关系并保存到文件
	system("cls");//清屏
	string filename;
	FILE* fp;
	char ch[100], od;
	memset(member, 0, sizeof(Man*) * 1000);
	Member* ret = NULL;
	cout << "请输入家族姓氏：";
	scanf("%s", ch);
	cout << endl;
	filename = ch;
	filename = filename + ".txt";
	fp = fopen(filename.c_str(), "r+");
	if (fp) {
		fclose(fp);
		printf("%s氏家族关系已存在！按Y打开，R重建,Q返回主菜单”\n\n", ch);
		od = getch();
		if (od == 'y' || od == 'Y')
		{
			ret = Open(filename);//调用打开函数
			return ret;
		}

	}
	if (!fp || od == 'R' || od == 'r') {
		fp = fopen(filename.c_str(), "w+");
		cout << "请按层次输入结点，每个结点信息占一行\n\n";
		cout << "兄弟输入结束以“@”为标志，结束标志为“#”，无配偶输入“N”，输入“!”返回主菜单\n\n";


		for (int i = 0;;) {
			string n;
			char name[100], sex;
			int age;
			cout << "姓名：";
			scanf("%s", name);
			Man* New = new Man;
			New->name = name;
			if (New->name == "!"|| New->name == "！") {//返回主菜单
				return NULL;
			}
			if (New->name == "#") {//输入结束
				member[i++] = New;
				fprintf(fp, "#\n");
				break;
			}
			else if (New->name == "@") {//兄弟输入结束
				fprintf(fp, "@\n");
				member[i++] = New;
			}
			else if (New->name != "@") {
				cout << "性别：";
				while (1) {
					sex = getche();
					printf("\n");
					if (sex != 'F' && sex != 'M') {//性别输入错误
						printf("请输入正确的性别（F/M）：");
					}
					else  break;
				}
				New->sex = sex;
				cout << "年龄：";
				scanf("%d", &age);
				New->age = age;
				cout << "配偶：";
				scanf("%s", name);
				n = name;
				if (n != "N") {//配偶
					New->spouse = new Man;
					New->spouse->name = n;
					cout << "性别：";
					while (1) {
						sex = getche();
						cout << endl;
						if (sex != 'F' && sex != 'M') {//性别输入错误
							cout << "请输入正确的性别（F/M）：";
						}
						else  break;
					}
					New->spouse->sex = sex;
					cout<<"年龄：";
					scanf("%d", &age);
					New->spouse->age = age;
				}
				member[i++] = New;
				fprintf(fp, "%6s %c %d ", New->name.c_str(), New->sex, New->age);
				if (New->spouse) {
					fprintf(fp, "配偶： %6s %c %d", New->spouse->name.c_str(), New->spouse->sex, New->spouse->age);
				}
				fprintf(fp, "\n");
			}
		}
		ret = Creat_Tree();//调用建树函数
		F = filename;
		
		fclose(fp);
		cout << "创建成功！\n";
		getch();
		Sleep(700);
		return ret;
	}
	else if (od == 'q' || od == 'Q') {
		return NULL;
	}

}
Member* Search(Member* FT, string name)//查找树
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
string GpPrint(Man *gp, Man* fa)//爷爷奶奶外公外婆
{
	int x=1, y=1;
	string ret;
	const char* gpre[2][20] = { {"爷爷","奶奶"},{"外公","外婆"} };
	if (gp->sex == 'M')y = 0;
	if (fa->sex == 'M')x = 0;
	ret = gpre[x][y];
	return ret;
}
string FaPrint(Man* fa) //父亲母亲
{
	if (fa->sex == 'M')return "父亲";
	else return"母亲";
}
string FabPrint(Man* fab,Man* fa) //父系的同系
{
	int x = 1, y = 2;
	string ret;
	const char* fare[2][20] = { {"伯父","叔父","姑姑"},{"舅舅","舅舅","姨妈"} };
	if (fab == fa)return "相同";
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
string BroPrint(Man* bro, Man* me)//同系
{
	int x = 1, y = 1;
	string ret;
	const char* brore[2][20] = { {"哥哥","姐姐"},{"弟弟","妹妹"} };
	if (bro->age > me->age)x = 0;
	if (bro->sex == 'M')y = 0;
	ret = brore[x][y];
	return ret;
}
string GsPrint(Man* gs, Man* so) //孙系
{
	int x = 1, y = 1;
	string ret;
	const char* gsre[2][20] = { {"孙子","孙女"},{"外孙","外孙女"} };
	if (gs->sex == 'M')y = 0;
	if (so->sex == 'M')x = 0;
	ret = gsre[x][y];
	return ret;

}
void Relation(Member* FT) {
	system("cls");//清屏
	Member* r;
	string name;
	char n[100];
	cout<<"查询者的名字：";
	scanf("%s", n);
	cout << endl;
	name = n;//换成string类型
	if (!FT) {
		cout << "请先建立家族树！\n";
		Sleep(700);
	}
	r = Search(FT, name);
	if (!r) {//没有找到
		cout<<"此人未在本家族树中显示！\n";
		Sleep(700);
		return;
	}
	Member* gp, * fa, * so, * gs,*fab,*bro;
	QUE<Member*>bf, sf, gg, jj, ym,ge,ji,di,me,ez,ne,sz,sn,ws,wn;
	

	while (1) {
		system("cls");//清屏
		printf("查询者的名字：%s",name.c_str());
		printf("\n\n%*c1.查询祖先", 32, ' ');
		printf("\n\n%*c2.查询爷系", 32, ' ');
		printf("\n\n%*c3.查询父系", 32, ' ');
		printf("\n\n%*c4.查询兄弟姐妹", 32, ' ');
		printf("\n\n%*c5.查询子女", 32, ' ');
		printf("\n\n%*c6.查询孙系", 32, ' ');
		printf("\n\n%*c0.退出查询", 32, ' ');
		printf("\n\n%*c请输入菜单编号进行选择：", 30, ' ');
		//查找菜单
		char ch;
		int order;
		ch = getch();
		cout << endl << endl;
		order = ch - '0';
		switch (order)
		{
		case 1:
			printf("%s的祖先是%s", name.c_str(), FT->man->name.c_str());//直接返回根节点
			cout << "\n\n按任意键返回上级菜单";
			ch = getch();
			break;
		case 2:
			if (!r->father) {//父系不存在则爷系不存在
				printf("%s的爷系未在本家族树中显示\n\n",name.c_str());
				cout << "\n\n按任意键返回上级菜单";
				ch = getch();
				break;
			}
			if (!r->father->father) {//爷系不存在
				printf("%s的爷系未在本家族树中显示\n\n",name.c_str());
				cout << "\n\n按任意键返回上级菜单";
				ch = getch();
				break;
			}
			gp = r->father->father;
			fa = r->father;
			printf("\n%s的%s是%s",name.c_str(),GpPrint(gp->man,fa->man).c_str(),gp->man->name.c_str());
			if(r->father->father->man->spouse)
				printf("\n%s的%s是%s", name.c_str(), GpPrint(gp->man->spouse, fa->man).c_str(), gp->man->spouse->name.c_str());
			cout << "\n\n按任意键返回上级菜单";
			ch = getch();
			break;
		case 3:
			if (!r->father) {//父系不存在
				printf("%s的父系未在本家族树中显示\n\n", name.c_str());
				cout << "\n\n按任意键返回上级菜单";
				ch = getch();
				break;
			}
			else {
				fa = r->father, fab = fa;

				printf("\n%s的%s是%s", name.c_str(), FaPrint(fa->man).c_str(), fa->man->name.c_str());
				if (fa->man->spouse)
					printf("\n%s的%s是%s", name.c_str(), FaPrint(fa->man->spouse).c_str(), fa->man->spouse->name.c_str());
				for (; fab->pre; fab = fab->pre);
				for (; fab; fab = fab->brother) {
					if (FabPrint(fab->man, fa->man) == "伯父")bf.push(fab);
					if (FabPrint(fab->man, fa->man) == "叔父")sf.push(fab);
					if (FabPrint(fab->man, fa->man) == "姑姑")gg.push(fab);
					if (FabPrint(fab->man, fa->man) == "舅舅")jj.push(fab);
					if (FabPrint(fab->man, fa->man) == "姨妈")ym.push(fab);
				}
				if (!bf.isempty())printf("\n%s的伯父是", name.c_str());
				while (!bf.isempty())printf("%s ", bf.front()->man->name.c_str());
				if (!sf.isempty())printf("\n%s的叔父是", name.c_str());
				while (!sf.isempty())printf("%s ", sf.front()->man->name.c_str());
				if (!gg.isempty())printf("\n%s的姑姑是", name.c_str());
				while (!gg.isempty())printf("%s ", gg.front()->man->name.c_str());
				if (!jj.isempty())printf("\n%s的舅舅是", name.c_str());
				while (!jj.isempty())printf("%s ", jj.front()->man->name.c_str());
				if (!ym.isempty())printf("\n%s的姨妈是", name.c_str());
				while (!ym.isempty())printf("%s ", ym.front()->man->name.c_str());
			}
			cout << "\n\n按任意键返回上级菜单";
			ch = getch();
			break;
		case 4:
			bro = r;
			for (; bro->pre; bro = bro->pre);
			if (r == bro) {//同系不存在
				printf("%s没有兄弟姐妹\n",name.c_str());
				printf("\n\n按任意键返回上级菜单");
				ch = getch();
				break;
			}
			else {
				for (; bro; bro = bro->brother) {
					if (BroPrint(bro->man, r->man) == "哥哥")ge.push(bro);
					if (BroPrint(bro->man, r->man) == "姐姐")ji.push(bro);
					if (BroPrint(bro->man, r->man) == "弟弟")di.push(bro);
					if (BroPrint(bro->man, r->man) == "妹妹")me.push(bro);
				}
				if (!ge.isempty())printf("\n%s的哥哥是", name.c_str());
				while (!ge.isempty())printf("%s ", ge.front()->man->name.c_str());
				if (!ji.isempty())printf("\n%s的姐姐是", name.c_str());
				while (!ji.isempty())printf("%s ", ji.front()->man->name.c_str());
				if (!di.isempty())printf("\n%s的弟弟是", name.c_str());
				while (!di.isempty())printf("%s ", di.front()->man->name.c_str());
				if (!me.isempty())printf("\n%s的妹妹是", name.c_str());
				while (!me.isempty())printf("%s ", me.front()->man->name.c_str());
			}
			cout << "\n\n按任意键返回上级菜单";
			ch = getch();
			break;
		case 5:
			if (!r->child) {//子系不存在
				printf("%s没有子女",name.c_str());
				cout << "\n\n按任意键返回上级菜单";
				ch = getch();
				break;
			}
			so = r->child;
			for (;so;so=so->brother) {
				if (so->man->sex == 'M')ez.push(so);
				else ne.push(so);
			}
			if (!ez.isempty())printf("\n%s的", name.c_str());
			while (!ez.isempty()) {
				so = ez.front();
				printf("\n儿子是%s",so->man->name.c_str());
				if (so->man->spouse)
					printf("，儿媳是%s", so->man->spouse->name.c_str());
			
			}
			if (!ne.isempty())printf("\n%s的", name.c_str());
			while (!ne.isempty()) {
				so = ne.front();
				printf("\n女儿是%s", so->man->name.c_str());
				if (so->man->spouse)
					printf("，女婿是%s", so->man->spouse->name.c_str());

			}
			cout << "\n\n按任意键返回上级菜单";
			ch = getch();
			break;
		case 6:
			if (!r->child) {//子系不存在则孙系不存在
				printf("%s的孙系未在本家族树中显示\n\n", name.c_str());
				cout << "\n\n按任意键返回上级菜单";
				ch = getch();
				break;
			}
			so = r->child;
			for(;so;so=so->brother){
				if (so->child)break;
			}
			if (!so) {//孙系不存在
				printf("%s的孙系未在本家族树中显示\n\n", name.c_str());
				cout << "\n\n按任意键返回上级菜单";
				ch = getch();
				break;
			}
			so = r->child;
			for (; so; so = so->brother) {
				gs = so->child;
				for (; gs; gs = gs->brother) {
					if (GsPrint(gs->man, so->man) == "孙子")sz.push(gs);
					if (GsPrint(gs->man, so->man) == "孙女")sn.push(gs);
					if (GsPrint(gs->man, so->man) == "外孙")ws.push(gs);
					if (GsPrint(gs->man, so->man) == "外孙女")wn.push(gs);
				}
			}
			if (!sz.isempty())printf("\n%s的孙子是", name.c_str());
			while (!sz.isempty())printf("%s ", sz.front()->man->name.c_str());
			if (!sn.isempty())printf("\n%s的孙女是", name.c_str());
			while (!sn.isempty())printf("%s ", sn.front()->man->name.c_str());
			if (!ws.isempty())printf("\n%s的外孙是", name.c_str());
			while (!ws.isempty())printf("%s ", ws.front()->man->name.c_str());
			if (!wn.isempty())printf("\n%s的外孙女是", name.c_str());
			while (!wn.isempty())printf("%s ", wn.front()->man->name.c_str());
			cout << "\n\n按任意键返回上级菜单";
			ch = getch();
			break;

		case 0:

			return;
		default:
			cout << "请输入正确的菜单编号！";
			break;
		}
	}
}
void Change(Member* FT)//修改成员信息
{
	system("cls");
	Member* r,*New,*T;
	Man* spouse,*child;
	string name;
	char n[100];
	int sign = 1;
	FILE* fp;
	QUE<Member*>Q;//调用链队
	cout<<"修改者的名字：";
	scanf("%s", n);
	cout << endl;
	name = n;
	if (!FT) {//家族树不存在
		cout << "请先建立家族树！\n";
		Sleep(700);
		return;
	}
	r = Search(FT, name);
	if (!r) {//找不到
		cout << "此人未在本家族树中显示！\n";
		Sleep(700);
		return;
	}
	else {
		while (1) {
			system("cls");//清屏
			printf("修改者的名字：%s", name.c_str());
			printf("\n\n%*c1.修改", 32, ' ');
			printf("\n\n%*c2.删除", 32, ' ');
			printf("\n\n%*c3.添加子女", 32, ' ');
			printf("\n\n%*c4.添加配偶", 32, ' ');
			printf("\n\n%*c0.退出查询", 32, ' ');
			printf("\n\n%*c请输入菜单编号进行选择：", 30, ' ');
			//菜单
			char ch;
			int order;
			ch = getch();
			order = ch - '0';
			cout << endl << endl;
			switch (order)
			{
			case 1:
				cout << "姓名：";
				scanf("%s", n);
				if (iss) r->man->spouse->name=n;
				else r->man->name=n;
				cout << "性别：";
				while (1) {
					if (iss)r->man->spouse->sex = getche();
					else r->man->sex = getche();
					cout << endl;
					if (r->man->sex != 'F' && r->man->sex != 'M' || r->man->spouse->sex != 'F' && r->man->spouse->sex != 'M') {
						cout << "请输入正确的性别（F/M）：";
					}
					else  break;
				}
				cout << "年龄：";
				if (iss)scanf("%d", &r->man->spouse->age);
				else scanf("%d", &r->man->age);
				cout << "修改成功！";
				Sleep(700);
				break;
			case 2:
				if (iss) {
					delete r->man->spouse;
					r->man->spouse = NULL;
					cout << "删除成功！";
					Sleep(700);
				}
				else {
					cout << "此成员已录入的后代将一起删除，是否删除该成员？（Y/N)";
					ch = getch();
					if (ch == 'Y' || ch == 'y') {
						if (r->brother)
							r->brother->pre = r->pre;
						r->pre->brother = r->brother;
						delete r;
						cout << "删除成功！";
						Sleep(700);
					}
				}
				fp = fopen(F.c_str(), "w+");
				fprintf(fp, "%6s %c %d ", FT->man->name.c_str(), FT->man->sex, FT->man->age);
				if (FT->man->spouse) {
					fprintf(fp, "配偶： %6s %c %d", FT->man->spouse->name.c_str(), FT->man->spouse->sex, FT->man->spouse->age);
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
							fprintf(fp, "配偶： %6s %c %d", T->man->spouse->name.c_str(), T->man->spouse->sex, T->man->spouse->age);
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
				cout << "姓名：";
				scanf("%s", n);
				child->name = n;
				cout << "性别：";
				while (1) {
					child->sex = getche();
					cout << endl;
					if (child->sex != 'F' && child->sex != 'M') {
						cout << "请输入正确的性别（F/M）：";
					}
					else  break;
				}
				cout << "年龄：";
				scanf("%d", &child->age);
				New->man = child;
				New->father = r;
				New->brother = r->child;
				if (r->child)
					r->child->pre = New;
				r->child = New;
				cout << "添加成功！";
				Sleep(700);
				break;
			case 4:
				spouse = new Man;
				if (r->man->spouse) {
					cout << "此成员已有配偶是否修改？(Y/N）";
					ch = getch();
					cout << endl << endl;
					if (ch != 'y' && ch != 'Y')break;
				}
				cout << "姓名：";
				scanf("%s",n);
				spouse->name = n;
				cout << "性别：";
				while (1) {
					spouse->sex = getche();
					cout << endl;
					if (spouse->sex != 'F' && spouse->sex != 'M') {
						cout << "请输入正确的性别（F/M）：";
					}
					else  break;
				}
				cout << "年龄：";
				scanf("%d", &spouse->age);
				r->man->spouse = spouse;
				cout << "添加成功！";
				Sleep(700);
				break;
			case 0:
				fp = fopen(F.c_str(), "w+");
				fprintf(fp, "%6s %c %d ", FT->man->name.c_str(), FT->man->sex, FT->man->age);
				if (FT->man->spouse) {
					fprintf(fp, "配偶： %6s %c %d", FT->man->spouse->name.c_str(), FT->man->spouse->sex, FT->man->spouse->age);
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
							fprintf(fp, "配偶： %6s %c %d", T->man->spouse->name.c_str(), T->man->spouse->sex, T->man->spouse->age);
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
			printf("\n\n%*c请输入正确的菜单编号！", 30, ' ');
			Sleep(700);
			break;
		}
	}
}