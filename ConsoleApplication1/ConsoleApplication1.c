#include <stdio.h>
#include <stdlib.h>
//NULL应与ElemType的一个值相同
typedef int ElemType;
//链表
struct  Link_Node {
	ElemType data;
	struct Link_Node *next;
};
typedef struct Link_Node LinkList;

//初始化线性表 OK-
void InitList(LinkList **L) {
	*L = (LinkList *)malloc(sizeof(LinkList));
	(*L)->data = NULL;
	(*L)->next = NULL;
	return;
}
//添加结点 OK-
void Add(LinkList* L, ElemType e) {
	LinkList *newnode = (LinkList *)malloc(sizeof(LinkList));
	LinkList *p = L;
	while (p!=NULL&&p->next != NULL) {
		p = p->next;
	}
	p->next = newnode;
	newnode->data = e;
	newnode->next = NULL;
	return;
}
//销毁线性表 OK
void DestroyList(LinkList **L) {
	LinkList **p = L, *q = (*p)->next;
	while (q != NULL)
	{
		free(*p);
		*p = q;
		q = (*p)->next;
	}
	free(*p);
	(*p)->next = NULL;
	(*p)->data = NULL;
}
//重置为空表 OK
void ClearList(LinkList **L) {
	DestroyList(L);
	InitList(L);
	return;
}
//判断线性表是否为空 OK
int ListEmpty(LinkList *L) {
	return(L == NULL||L->next == NULL);
}
//返回表长度 OK-
int ListLength(LinkList *L) {
	if (L == NULL||(L->data==NULL&&L->next==NULL))return 0;
	int len = 1;
	LinkList *p = L;
	while (p->next != NULL) {
		len++; p = p->next;
	}
	return len;
}
//获取指定表元素 获取到为1 未获取为0 OK-
int GetElem(LinkList *L, int i, ElemType *e) {
	if (i < 1) {
		*e = NULL; return 0;
	}
	LinkList *p = L;
	int j = 0;
	for (; j<i - 1; j++) {
		if (p->next != NULL)
			p = p->next;
		else {
			*e = NULL;
			return 0;
		}
	}
	*e = p->data;
	return 1;
}
//获取相同元素 返回index位置 OK
int LocateElem(LinkList * L, ElemType e, int(*compare)(ElemType e1, ElemType e2)) {
	LinkList *p = L;
	int result = 0, find = 0;
	while (p->next != NULL) {
		if ((!(*compare)(e, p->data)) && find == 0) {
			result++;
			p = p->next;
		}
		else {
			find = 1;
			result++;
			break;
		}
	}
	if ((*compare)(e, p->data) && find == 0) {
		find = 1;
		result++;
	}
	if (find == 0)return 0;
	else return result;
}
//比较相同函数 OK
int compare(ElemType e1, ElemType e2) {
	if (e1 == e2) {
		return 1;
	}
	else {
		return 0;
	}
}
//获取前驱元素 获取到为1 未获取为0 OK
int PriorElem(LinkList *L, ElemType cur_e, ElemType *pre_e) {
	LinkList *p = L;
	while (p->next != NULL) {
		LinkList* k = p->next;
		if (k->data == cur_e) {
			*pre_e = p->data;
			return 1;
		}
		p = k;
	}
	*pre_e = -1;
	return 0;
}
//获取后继元素 获取到为1 未获取为0 OK
int NextElem(LinkList *L, ElemType cur_e, ElemType *next_e) {
	LinkList *p = L;
	while (p->next != NULL) {
		LinkList* k = p->next;
		if (p->data == cur_e) {
			*next_e = k->data;
			return 1;
		}
		p = k;
	}
	*next_e = -1;
	return 0;
}
//插入元素 插入为1 未插入为0 OK-
int ListInsert(LinkList** L, int i, ElemType e) {
	if (i < 1)return 0;
	LinkList *p = *L;
	int j = 0;
	LinkList* m = NULL;
	for (; j<(i - 1); j++) {
		m = p;
		if (p->next != NULL || j==(i-2))p = p->next;
		else return 0;
	}
	LinkList *k = (LinkList *)malloc(sizeof(LinkList));
	k->data = e;
	if (m!=NULL) {
		m->next = k;
	}
	k->next = p;
	if (i == 1) {
		*L = k;
	}
	return 1;
}
//删除链表指定元素 删除成功为1 未删除为0 OK
int ListDelete(LinkList **L, int i, ElemType *e) {
	if (i < 1)return 0;
	LinkList *p = *L;
	int j = 0;
	LinkList* m = NULL;
	for (; j<(i - 1); j++) {
		m = p;
		if (p!=NULL&&p->next != NULL)p = p->next;
		else return 0;
	}
	*e = p->data;
	if (m!= NULL) {
		m->next = p->next;
	}
	else *L = p->next;
	free(p);
	return 1;
}
//访问函数 OK
int visit(ElemType *p) {
	if (sizeof(p) == sizeof(ElemType))return 1;
	else return 0;
	//return 0;
}
//是否可访问 OK
int ListTraverse(LinkList *L, int(*visit)(ElemType *e)) {
	LinkList *p = L;
	if (p != NULL) {
		while (p->next != NULL) {
			if (!visit(&(p->data)))return 0;
			p = p->next;
		}
		if (!visit(&(p->data)))return 0;
	}
	return 1;
}
//归并排序 OK
void MergeList(LinkList *La, LinkList *Lb, LinkList **Lc) {
	InitList(Lc);
	int i = 1, j = 1, k = 0, La_Len = ListLength(La), Lb_Len = ListLength(Lb);
	ElemType *ai = (ElemType *)malloc(sizeof(ElemType));
	ElemType *bj = (ElemType *)malloc(sizeof(ElemType));
	while ((i <= La_Len) && (j <= Lb_Len)) {
		//La和Lb非空
		GetElem(La, i, ai); GetElem(Lb, j, bj);
		if (*ai <= *bj) { ListInsert(Lc, ++k, *ai); ++i; }
		else { ListInsert(Lc, ++k, *bj); ++j; }
	}
	while (i <= La_Len) {
		GetElem(La, i++, ai); ListInsert(Lc, ++k, *ai);
	}
	while (j <= Lb_Len) {
		GetElem(Lb, j++, bj); ListInsert(Lc, ++k, *bj);
	}
	ElemType e=-1;
	ListDelete(Lc, ListLength(*Lc), &e);
	free(ai);
	free(bj);
	return;
}
//遍历输出 OK
void GetAllList(LinkList *p) {
	while (p != NULL&&p->next != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	if(p != NULL)printf("%d ", p->data);
	printf("\n");
	return;
}
int main()
{
	//初始化的p必须指向NULL
	LinkList *LA=NULL,*LB=NULL,*LC=NULL;
	ElemType e;

	InitList(&LA);
	InitList(&LB);

	Add(LA, 3);
	Add(LA, 5);
	Add(LA, 8);
	Add(LA, 11);
	ListDelete(&LA, 1, &e);

	Add(LB, 2);
	Add(LB, 6);
	Add(LB, 8);
	Add(LB, 9);
	Add(LB, 11);
	Add(LB, 15);
	Add(LB, 20);
	ListDelete(&LB, 1, &e);

	MergeList(LA, LB, &LC);
	printf("归并后：");
	GetAllList(LC);
	ListTraverse(LC, visit);
	//增加
	printf("增加后：");
	Add(LC, 30);
	GetAllList(LC);
	//删除
	ListDelete(&LC, ListLength(LC), &e);
	printf("删除后：");
	GetAllList(LC);
	//查找
	//1.通过索引
	int i = 2;
	GetElem(LC, i, &e);
	printf("1.查找第二位：%d\n", e);
	//2.通过值查找第一个符合项
	int index = LocateElem(LC, e, compare);
	GetElem(LC, index, &e);
	printf("2.查找第二位：%d\n", e);
	//修改
	int j = 1;
	ListDelete(&LC, j, &e);
	ListInsert(&LC, j, 1024);
	printf("修改1位后：");
	GetAllList(LC);

	system("pause");
	return 0;
}