/*
 * ���Լ���:
 *
 *  1. ��ʱ��С�����ʼֵ
 *
 *  2. ��ɢ�б���ĳ��������������Ԫ�ض��ܵ�ͬһ��ɢ��Ͱ��
 *
 *  3. �Զ���洢���亯���������ڴ����ʧ�ܳ���(testmalloc)
 *
 */

/* testmalloc: return NULL after 10 calls */
void* testmalloc(size_t n)
{
    static int count = 0;

    if (++count > 10)
        return NULL;
    else
        return malloc(n);
}
