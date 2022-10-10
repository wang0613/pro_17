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
    //指针数组
    int *arr[10];

    //数组指针
    int *(*pa)[10] = &arr;

    //函数指针
    int (*padd)(int, int) =add;
//    int rs = (*padd)(10,20);
//    int rs = padd(10,20); 两种写法都ok

    //函数指针的数组
    int (*pArr[10])(int, int) ={0, add};

    //指向 数组指针 的指针
    int (*(*ppArr)[10])(int, int) =pArr;
    return 0;
}

//对int 类型进行排序
int cmp_int(const void *e1, const void *e2) {
    //void* 可以接收任意类型的地址 注意:void* 类型不能进行解引用操作
    //两个数相等时 返回0
    //大于返回正数
    //小于返回负数
    return *(int *) e1 - *(int *) e2;
}

int cmp_float(const void *e1, const void *e2) {
    return (int) (*(float *) e1 - *(float *) e2);
}

int cmp_stu_by_age(const void *e1, const void *e2) {
    return (((struct stu *) e1)->age) - (((struct stu *) e2)->age);
}

int cmp_stu_by_name(const void *e1, const void *e2) {
    //比较名字就是比较字符串
    //字符串的比较不能直接使用 >  < =, 应该使用strcmp(str1,str2)
    return strcmp(((struct stu *) e1)->name, ((struct stu *) e2)->name);
}

//比较整形
void test1() {

    int arr[10] = {8, 65, 3, 2, 15, 6, 7};
    int sz = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, sz, sizeof(arr[0]), cmp_int);

    int i = 0;
    for (i = 0; i < sz; i++) {
        printf("%d ", arr[i]);
    }
}

//比较浮点型
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
    //第一个参数:待排序数组的元素地址
    //第二个参数:待排序数组的元素个数
    //第三个参数:待排序数组的每一个元素的大小-单位是字节
    //第四个参数：函数指针，比较两个元素所用函数的地址
    qsort(s, sz, sizeof(s[0]), cmp_stu_by_name);

    int i = 0;
    for (i = 0; i < sz; i++) {
        printf("%s\t%d\n", s[i].name, s[i].age);
    }
}
//当一个一个字符交换时，需要告诉 当前字符有多少字节， 需要交换几次
//int = 4 char=1  交换一次int需要4次
void swap(char* buf1,char* buf2,int width)
{
    int i = 0;
    for(i = 0; i< width; i++)
    {
        //交换一对字符， int需要4次
        char temp = *buf1;
        *buf1 = *buf2;
        *buf2 = temp;
        //将指针的步长 进行++，移项下一个字符
        buf1++;
        buf2++;

    }
}

//改造冒泡排序  cmp为自定义排序方法
void bubble_sort_grade(void *base, int sz, int width,int(*cmp)(void* e1,void* e2)) {
    int i = 0;
    for (i = 0; i < sz - 1; i++) {
        int j = 0;
        for (j = 0; j < sz - 1 - i; j++) {

            //两个元素的比较: 抽离不同类型的函数。存放函数指针， 根据传入的函数指针，进行调用不同的函数
            //(char*)(base)+字节长度： 就是1+步长
            char* e1 = (char*)base+j*width;
            char* e2= (char*)base+(j+1)*width;
            if(cmp(e1,e2) > 0) //回调函数:cmp
            {
                //交换
                swap(e1,e2,width);
            }

        }
    }

}

void test4() {
    int arr[] = {8, 7, 65, 5, 4, 12};
    int sz = sizeof(arr) / sizeof(arr[0]);
    //程序员一定知道自己排序的是什么数据，
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
