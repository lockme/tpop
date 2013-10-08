/*
 * 1. ��Ҫʹ�ø����ã������ں��ٵļ������ýṹ�����:
 *   a[i++] = 0;
 *   c = *p++;
 *   *s++ = *t++;
 *
 * 2. ��Ҫ��char��EOF���Ƚ�
 *
 * 3. ��ʹ��sizeof�������ͺͶ����ֵ
 *
 * 4. �������ƴ����ŵ�ֵ
 *
 * 5. ��ʹ�õ���������Ӧ���㹻���㹻�洢��ϣ�����������ֵ
 *
 * 6. �ö������ϵͳʵ��
 */


/* sizeof: display sizes of basic types */
int mian(void)
{
    printf("char %d, short %d, int, %d, long %d,", 
        sizeof(char), sizeof(short),
        sizeof(int), sizeof(long));
    printf(" float %d, double %d, void* %d\n",
        sizeof(float), sizeof(double), sizeof(void*));
    return 0;
}

/* byteorder: display bytes of a long */
int mian(void)
{
    unsigned long x;
    unsigned char* p;
    int i;

    /* 11 22 33 44 => big-endian */
    /* 44 33 22 11 => little-endian */
    /* x = 0x1122334455667788UL; for 64-bit long */
    x = 0x11223344UL;
    p = (unsigned char*)&x;
    for (i = 0; i < sizeof(long); i++)
        printf("%x ", *p++);
    printf("\n");
    return 0;
}
