#include <stdio.h>
#include <stdlib.h>  //qsort()
#include <string.h>  //strcmp()

int add(int x, int y) {
    return x + y;
}

struct stu {
    char name[20];
    int age;
};

void bubble_sort(int arr[], int sz) {
    int i = 0;
    for (i = 0; i < sz - 1; i++) {
        int j = 0;
        for (j = 0; j < sz - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main1() {
    //ָ������
    int *arr[10];

    //����ָ��
    int *(*pa)[10] = &arr;

    //����ָ��
    int (*padd)(int, int) =add;
//    int rs = (*padd)(10,20);
//    int rs = padd(10,20); ����д����ok

    //����ָ�������
    int (*pArr[10])(int, int) ={0, add};

    //ָ�� ����ָ�� ��ָ��
    int (*(*ppArr)[10])(int, int) =pArr;
    return 0;
}

//��int ���ͽ�������
int cmp_int(const void *e1, const void *e2) {
    //void* ���Խ����������͵ĵ�ַ ע��:void* ���Ͳ��ܽ��н����ò���
    //���������ʱ ����0
    //���ڷ�������
    //С�ڷ��ظ���
    return *(int *) e1 - *(int *) e2;
}

int cmp_float(const void *e1, const void *e2) {
    return (int) (*(float *) e1 - *(float *) e2);
}

int cmp_stu_by_age(const void *e1, const void *e2) {
    return (((struct stu *) e1)->age) - (((struct stu *) e2)->age);
}

int cmp_stu_by_name(const void *e1, const void *e2) {
    //�Ƚ����־��ǱȽ��ַ���
    //�ַ����ıȽϲ���ֱ��ʹ�� >  < =, Ӧ��ʹ��strcmp(str1,str2)
    return strcmp(((struct stu *) e1)->name, ((struct stu *) e2)->name);
}

//�Ƚ�����
void test1() {

    int arr[10] = {8, 65, 3, 2, 15, 6, 7};
    int sz = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, sz, sizeof(arr[0]), cmp_int);

    int i = 0;
    for (i = 0; i < sz; i++) {
        printf("%d ", arr[i]);
    }
}

//�Ƚϸ�����
void test2() {
    float arr[] = {1.0, 4, 5, 3, 4.4};

    int sz = sizeof(arr) / sizeof(arr[0]);
    qsort(arr, sz, sizeof(arr[0]), cmp_float);

    int i = 0;
    for (i = 0; i < sz; i++) {
        printf("%f ", arr[i]);
    }
}

void test3() {
    struct stu s[3] = {{"zhangsan", 20},
                       {"lisi",     38},
                       {"wangwu",   19}};
    int sz = sizeof(s) / sizeof(s[0]);
    //��һ������:�����������Ԫ�ص�ַ
    //�ڶ�������:�����������Ԫ�ظ���
    //����������:�����������ÿһ��Ԫ�صĴ�С-��λ���ֽ�
    //���ĸ�����������ָ�룬�Ƚ�����Ԫ�����ú����ĵ�ַ
    qsort(s, sz, sizeof(s[0]), cmp_stu_by_name);

    int i = 0;
    for (i = 0; i < sz; i++) {
        printf("%s\t%d\n", s[i].name, s[i].age);
    }
}
//��һ��һ���ַ�����ʱ����Ҫ���� ��ǰ�ַ��ж����ֽڣ� ��Ҫ��������
//int = 4 char=1  ����һ��int��Ҫ4��
void swap(char* buf1,char* buf2,int width)
{
    int i = 0;
    for(i = 0; i< width; i++)
    {
        //����һ���ַ��� int��Ҫ4��
        char temp = *buf1;
        *buf1 = *buf2;
        *buf2 = temp;
        //��ָ��Ĳ��� ����++��������һ���ַ�
        buf1++;
        buf2++;

    }
}

//����ð������  cmpΪ�Զ������򷽷�
void bubble_sort_grade(void *base, int sz, int width,int(*cmp)(void* e1,void* e2)) {
    int i = 0;
    for (i = 0; i < sz - 1; i++) {
        int j = 0;
        for (j = 0; j < sz - 1 - i; j++) {

            //����Ԫ�صıȽ�: ���벻ͬ���͵ĺ�������ź���ָ�룬 ���ݴ���ĺ���ָ�룬���е��ò�ͬ�ĺ���
            //(char*)(base)+�ֽڳ��ȣ� ����1+����
            char* e1 = (char*)base+j*width;
            char* e2= (char*)base+(j+1)*width;
            if(cmp(e1,e2) > 0) //�ص�����:cmp
            {
                //����
                swap(e1,e2,width);
            }

        }
    }

}

void test4() {
    int arr[] = {8, 7, 65, 5, 4, 12};
    int sz = sizeof(arr) / sizeof(arr[0]);
    //����Աһ��֪���Լ��������ʲô���ݣ�
    bubble_sort_grade(arr, sz, sizeof(arr[0]), cmp_int);

    int i = 0;
    for (i = 0; i < sz; i++) {
        printf("%d ", arr[i]);
    }
}

void test5() {
    struct stu s[3] = {{"zhangsan", 20},
                       {"lisi",     38},
                       {"wangwu",   19}};
    int sz = sizeof(s) / sizeof(s[0]);
    bubble_sort_grade(s,sz,sizeof(s[0]),cmp_stu_by_age);

    int i = 0;
    for (i = 0; i < sz; i++) {
        printf("%s\t%d\n", s[i].name, s[i].age);
    }
}

int main() {
    test5();
}
