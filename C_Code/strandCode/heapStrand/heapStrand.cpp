/*
 * @explain: Copyright (c) 2020 WEI.ZHOU. All rights reserved.
 * The following code is only used for learning and communication, not for illegal and commercial use.
 * If the code is used, no consent is required, but the author has nothing to do with any problems 
 * and consequences.
 * 
 * In case of code problems, feedback can be made through the following email address.
 * 						<xiaoandx@gmail.com>
 * 
 * @Description: 利用堆实现串
 * @Author: WEI.ZHOU
 * @Date: 2020-10-28 19:00:18
 * @Version: V1.0
 * @LastEditTime: 2020-10-28 20:56:28
 * @LastEditors: WEI.ZHOU
 * @Others: 
 */
#include <iostream>
#include <string.h>

#define INIT_STRAND_SIZE 255
#define OPERATION_SUCCESS 1
#define OPERATION_ERROR 0
#define VALUE_NEGATIVE -1
#define DEF_ONE 1
#define DEF_ZERO 0
#define LF '\n'

typedef struct{
    char *ch;
    int length;
}heapStr;

/**
 * @brief   初始化
 * @Date    2020-10-28 19:15:23
 * @param   heapStr &s 需要初始化的串
 */
void initStr(heapStr &s);

/**
 * @brief   初始化字符串
 * @Date    2020-10-28 19:18:05
 * @param   heapStr &s 需要初始化的串
 * @param   char v[] 需要初始化的字符串
 * @return  {int} 1 -> 操作成功; 0 -> 操作失败
 */
int strAssign(heapStr &s, char v[]);

/**
 * @brief   输出打印串
 * @Date    2020-10-28 19:28:43
 * @param   heapStr s 需要操作的串
 */
void strPrint(heapStr s);

/**
 * @brief   串的复制
 * @Date    2020-10-28 19:43:06
 * @param   heapStr s 需要被复制的串
 * @param   heapStr &T 需要复制得到的串
 * @return  {int} 1 -> 操作成功; 0 -> 操作失败
 */
int strCopy(heapStr s, heapStr &T);

/**
 * @brief   获取串的长度
 * @Date    2020-10-28 19:41:31
 * @param   heapStr s 需要操作获取的串
 * @return  {int} 串的长度
 */
int getStrLength(heapStr s);

/**
 * @brief   清空串
 * @Date    2020-10-28 19:45:00
 * @param   heapStr s 需要操作的串
 * @return  {int} 1 -> 操作成功; 0 -> 操作失败
 */
int strClear(heapStr &s);

/**
 * @brief   两个字符串比较
 * @Date    2020-10-28 19:49:54
 * @param   heapStr s 需要比较操作的串
 * @param   heapStr T 需要比较操作的串
 * @return  {int} 等于0-> s=T; 大于0->s>T; 小于0 ->s<T
 */
int strCompare(heapStr s, heapStr T);

/**
 * @brief   两个串合并成新串
 * @Date    2020-10-28 19:57:30
 * @param   heapStr &T 合并得到的新串
 * @param   heapStr s 合并的新串
 * @param   heapStr s2 合并的新串
 * @return  {int} 1 -> 操作成功; 0 -> 操作失败
 */
int strConcat(heapStr &T, heapStr s, heapStr s2);

/**
 * @brief   截取一个串的指定位置长度
 * @Date    2020-10-28 20:07:26
 * @param   heapStr &T 截取得到的新串
 * @param   heapStr s 截取的串
 * @param   int pos 截取起点(包括)
 * @param   int len 截取长度
 * @return  {int} 1 -> 操作成功; 0 -> 操作失败
 */
int subString(heapStr &T, heapStr s, int pos, int len);

/**
 * @brief   判断是否为空
 * @Date    2020-10-28 20:34:07
 * @param   heapStr T 需要判断的串
 * @return  {int} 1->不为空;0->为空 
 */
int strEmpty(heapStr T);

/**
 * @brief   向指定串中对应起点插入串
 * @Date    2020-10-28 20:38:44
 * @param   heapStr &s 被插入的串
 * @param   int pos 被插入的起点
 * @param   heapStr T 插入的串
 * @return  {int} 1 -> 操作成功; 0 -> 操作失败
 */
int strInsert(heapStr &s, int pos, heapStr T);

/**
 * @brief   删除串的指定位置起指定长度的串
 * @Date    2020-10-28 20:46:52
 * @param   heapStr &T 被删除的串
 * @param   int pos 删除的起点
 * @param   int len 删除的长度
 * @return  {int} 1 -> 操作成功; 0 -> 操作失败
 */
int strDelete(heapStr &T, int pos, int len);

int main(){
    heapStr hs,hs2,hs3,hs4;
    initStr(hs);
    strAssign(hs,(char *)"hello");
    strPrint(hs);
    strCopy(hs,hs2);
    strPrint(hs2);
    std::cout<<getStrLength(hs)<<LF;
    std::cout<<"比较大小:"<<strCompare(hs,hs2)<<LF;
    // strClear(hs2);
    strConcat(hs3,hs,hs2);
    std::cout<<"hs3 = hs+hs2:";
    strPrint(hs3);
    subString(hs4,hs,1,2);
    std::cout<<"hs4 = hs 2 2:";
    strPrint(hs4);
    strEmpty(hs);
    strInsert(hs,3,hs2);
    strDelete(hs,2,2);
    return OPERATION_SUCCESS;
}

void initStr(heapStr &s){
    s.ch = NULL;
    s.length = DEF_ZERO;
}

int strAssign(heapStr &s,char v[]){
    if(s.ch != NULL){ free(s.ch);}
    int len = strlen(v);
    if(DEF_ZERO == len){ initStr(s); return OPERATION_SUCCESS;}
    s.ch = (char *)malloc(len * sizeof(char));
    if(!s.ch){ return OPERATION_ERROR;}
    for(int i = DEF_ZERO; i<len; i++){
        s.ch[i] = v[i];
    }
    s.length = len;
    return OPERATION_SUCCESS;
}

void strPrint(heapStr s){
    for(int i = DEF_ZERO; i<s.length; i++){
        std::cout<<s.ch[i];
    }
    std::cout<<LF;
}

int strCopy(heapStr s,heapStr &T){
    initStr(T);
    T.ch = (char *)malloc(s.length * sizeof(char));
    if(!T.ch){ return OPERATION_ERROR;}
    for(int i = DEF_ZERO; i<s.length; i++){
        T.ch[i] = s.ch[i];
    }
    T.length = s.length;
    return OPERATION_SUCCESS;
}

int getStrLength(heapStr s){    return s.length;}

int strClear(heapStr &s){
    if(s.ch){
        free(s.ch);
        s.ch = NULL;
    }
    s.length = DEF_ZERO;
    return OPERATION_SUCCESS;
}

int strCompare(heapStr s,heapStr T){
    for(int i = DEF_ZERO; i<s.length && i<T.length; i++){
        if(s.ch[i] != T.ch[i]){
            return s.ch[i] - T.ch[i];
        }
    }
    return s.length - T.length;
}

int strConcat(heapStr &T,heapStr s,heapStr s2){
    initStr(T);
    T.ch = (char *)malloc((s.length + s2.length)*sizeof(char));
    if(!T.ch){ return OPERATION_ERROR;}
    for(int i = DEF_ZERO; i<s.length; i++){
        T.ch[i] = s.ch[i];
    }
    for(int i = DEF_ZERO; i<s2.length; i++){
        T.ch[i + s.length] = s2.ch[i];
    }
    T.length = s.length + s2.length;
    return OPERATION_SUCCESS;
}

int subString(heapStr &T, heapStr s, int pos, int len){
    initStr(T);
    if(DEF_ZERO > pos ||\
        s.length <= pos ||\
        s.length < (pos + len) ||\
        DEF_ZERO > len){ return OPERATION_ERROR;}
    T.ch = (char *)malloc(len * sizeof(char));
    if(!T.ch){ return OPERATION_ERROR;}
    for(int i = pos; i<=pos+len; i++){
        T.ch[i-pos] = s.ch[i];
    }
    T.length = len;
    return OPERATION_SUCCESS;
}

int strEmpty(heapStr T){
    if(DEF_ZERO < T.length){ return OPERATION_SUCCESS;}
    return OPERATION_ERROR;
}

int strInsert(heapStr &s, int pos, heapStr T){
    if(DEF_ZERO > pos || s.length < pos){ return OPERATION_ERROR;}
    s.ch = realloc(s.ch,(s.length + T.length) * sizeof(char));
    if(!s.ch){ return OPERATION_ERROR;}
    for(int i = s.length - DEF_ONE; i>=pos; i--){
        s.ch[i + T.length] =s.ch[i]; 
    }
    for(int i = DEF_ZERO; i<T.length;i++){
        s.ch[i + pos] = T.ch[i];
    }
    s.length += T.length;
    return OPERATION_SUCCESS;
}

int strDelete(heapStr &T, int pos, int len){
    if(DEF_ZERO > pos ||\
         DEF_ZERO > len || T.length < pos ||\
          T.length < (pos+len)){ return OPERATION_ERROR;}
    for(int i = pos; i<=T.length; i++){
        T.ch[i] = T.ch[i + len];
    }
    T.length -= len;
    T.ch = (char *)realloc(T.ch,T.length * sizeof(char));
    if(!T.ch){ return OPERATION_ERROR;}
    return OPERATION_SUCCESS;
}