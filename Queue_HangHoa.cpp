#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*==================================================*/
struct HangHoa
{
	char maHang[10];
	char tenHang[20];
	char DVT[10];
	int soLuong;
};

struct QNode
{
	HangHoa info;
	QNode *next;
};

struct Queue
{
	QNode *head;
	QNode *tail;
};

void khoiTaoQueue(Queue &queue)
{
	queue.head = queue.tail = NULL;
}

QNode *taoQNode(HangHoa h)
{
	QNode *p = new QNode;
	if (p != NULL)
	{
		p->info = h;
		p->next = NULL;
	}
	return p;
}

bool kiemTraRong(Queue queue)
{
	return queue.head == NULL;
}

void themQNode(Queue &queue, QNode *p) //Them cuoi queue
{
	if (p == NULL) return;
	if (kiemTraRong(queue))
		queue.head = queue.tail = p;
	else
	{
		queue.tail->next = p;
		queue.tail = p;
	}
}

void xoaQNode(Queue &queue, HangHoa &h) //Xoa dau queue
{
	if (kiemTraRong(queue)) return;
	QNode *p = queue.head;
	queue.head = queue.head->next;
	if (queue.head == NULL)
		queue.tail = NULL;
	h = p->info;
	delete p;
}

void nhapHH(HangHoa &h)
{
	printf("========================\n");
	printf("Nhap ma hang: ");
	scanf("%s", h.maHang);
	printf("Nhap ten hang: ");
	scanf("%s", h.tenHang);
	printf("Nhap don vi tinh: ");
	scanf("%s", h.DVT);
	printf("Nhap so luong: ");
	scanf("%d", &h.soLuong);
	printf("========================\n");
}

void xuatHH(HangHoa h)
{
	printf("%10s \t %10s \t %5s \t%d\n", h.maHang, h.tenHang, h.DVT, h.soLuong);
}

void taoQueue(Queue &queue)
{
	khoiTaoQueue(queue);
	int n;
	do
	{
		printf("Nhap so luong: ");
		scanf("%d", &n);
	} while (n < 0);
	for (int i = 0; i < n; i++)
	{
		HangHoa h;
		nhapHH(h);
		themQNode(queue, taoQNode(h));
	}
}

void taoQueueFile(Queue &queue, char *tenFile)
{
	khoiTaoQueue(queue);
	FILE *f = fopen(tenFile, "r");
	if (f == NULL) return;
	else
	{
		while (!feof(f))
		{
			HangHoa h;
			fscanf(f, "%s", h.maHang);
			fscanf(f, "%s", h.tenHang);
			fscanf(f, "%s", h.DVT);
			fscanf(f, "%d", &h.soLuong);
			themQNode(queue, taoQNode(h));
		}
	}
	fclose(f);
}

void xuatQueue(Queue queue)
{
	printf("%10s \t %10s \t %5s \t%s\n", "Ma hang", "Ten hang", "DVT", "So Luong");
	QNode *p = queue.head;
	while (p != NULL)
	{
		xuatHH(p->info);
		p = p->next;
	}
}

void hangHoaXuatKho(Queue queue)
{
	if (kiemTraRong(queue)) return;
	QNode *p = queue.head;
	xuatHH(p->info);
}

void hangHoaNhapKho(Queue queue)
{
	if (kiemTraRong(queue)) return;
	QNode *p = queue.tail;
	xuatHH(p->info);
}

QNode *timQNode(Queue queue, char maHH[10])
{
	QNode *p = queue.head;
	while (p != NULL)
	{
		if (strcmp(p->info.maHang, maHH) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

static void menu()
{
	printf("========================\n");
	printf("1. Tao queue tu file\n");
	printf("2. Xuat queue tu file\n");
	printf("3. Thong tin hang chuan bi xuat\n");
	printf("4. Thong tin hang vua nhap\n");
	printf("5. Tim thong tin mat hang\n");
	printf("========================\n");
}
/*==================================================*/

void main()
{
	Queue queue;
	int choice;
	do
	{
		menu();
		printf("Nhap lua chon: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
		{
				  //taoQueue(queue);
				  printf("1. Tao queue tu file\n");
				  printf("Thong bao: Da doc duoc file du lieu\n");
				  taoQueueFile(queue, "DS_HangHoa.txt");
				  break;
		}
		case 2:
		{
				  printf("2. Xuat queue tu file\n");
				  xuatQueue(queue);
				  break;
		}
		case 3:
		{
				  printf("3. Thong tin hang chuan bi xuat\n");
				  hangHoaXuatKho(queue);
				  break;
		}
		case 4:
		{
				  printf("4. Thong tin hang vua nhap\n");
				  hangHoaNhapKho(queue);
				  break;
		}
		case 5:
		{
				  char maHH[10];
				  printf("Nhap ma hang hoa can tim: ");
				  scanf("%s", maHH);
				  QNode *p = timQNode(queue, maHH);
				  if (p == NULL)
					  printf("Thong bao: Khong co ma hang hoa trong queue\n");
				  else
					  xuatHH(p->info);
				  break;
		}
		default:
			break;
		}
	} while (choice != 0);
	system("pause");
}

