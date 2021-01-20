#include <cstdio>
#pragma warning(disable:4996)
#define tail 200001

struct person {
	int before = 0;
	int next = 0;
};

person queue[tail+1];

int main() {
	//announcement
	void insert();
	void del();
	void change();
	void reverse();

	//initialization
	queue[0].before = -1;
	queue[tail].next = -1;

	//data input
	int times = 0;
	for (int i = 0; i < 4; i++) {
		int k; scanf("%d", &k);
		times += k;
	}

	//operate
	for (int i = 0; i < times; i++) {
		int choice; scanf("%d", &choice);
		switch (choice) {
		case 1:insert(); break;
		case 0:del(); break;
		case -1:change(); break;
		case -2:reverse(); break;
		default:break;
		}
	}

	//data output
	person tmp = queue[0];
	while (tmp.next != tail) {
		printf("%d ", tmp.next);
		tmp = queue[tmp.next];
	}
	printf("-1");

	return 0;
}

void insert() {
	int i; int j; int choice;
	scanf("%d", &i); scanf("%d", &j); scanf("%d", &choice);

	if (j == -1) {
		//队伍第一人
		queue[0].next = i;
		queue[i].before = 0;
		queue[tail].before = i;
		queue[i].next = tail;
	}
	else {
		if (choice) {
			//往后插入
			queue[i].next = queue[j].next;
			queue[queue[j].next].before = i;
			queue[j].next = i;
			queue[i].before = j;
		}
		else {
			//向前插入
			queue[queue[j].before].next = i;
			queue[i].before = queue[j].before;
			queue[i].next = j;
			queue[j].before = i;
		}
	}
}

void del() { //删除学生
	int i; scanf("%d", &i);
	queue[queue[i].before].next = queue[i].next;
	queue[queue[i].next].before = queue[i].before;
}
/*
void bychange(int i,int j) {
	queue[queue[i].before].next = j;
	queue[j].before = queue[i].before;
	queue[queue[j].next].before = j;
	queue[i].next = queue[j].next;
	queue[i].before = j;
	queue[j].next = i;
}*/

void change() {
	int i; int j; scanf("%d", &i); scanf("%d", &j);
	
	if (queue[i].next = j) { //j在i后面
		queue[queue[i].before].next = j;
		queue[j].before = queue[i].before;
		queue[queue[j].next].before = j;
		queue[i].next = queue[j].next;
		queue[i].before = j;
		queue[j].next = i;
	}
	else if (queue[j].next = i) { //i在j后面
		queue[queue[j].before].next = i;
		queue[i].before = queue[j].before;
		queue[queue[i].next].before = i;
		queue[j].next = queue[i].next;
		queue[j].before = i;
		queue[i].next = j;
	}
	else {//i和j不相邻
		int inext = queue[i].next;
		int jbefore = queue[j].before;

		queue[queue[i].before].next = j;
		queue[j].before = queue[i].before;
		queue[queue[j].next].before = i;
		queue[i].next = queue[j].next;
		queue[inext].before = j;
		queue[j].next = inext;
		queue[i].before = jbefore;
		queue[jbefore].next = i;
	}

}

void reverse() {
	queue[0].next = queue[tail].before;
	queue[tail].before = queue[0].next;
	person tmp = queue[0];
	while (tmp.next != tail) {
		tmp = queue[tmp.next];
		int swap = tmp.before;
		tmp.before = tmp.next;
		tmp.next = swap;
	}
	queue[queue[0].next].before = 0;
	queue[queue[tail].before].next = tail;
}