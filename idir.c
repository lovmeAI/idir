/**
* ����ͼ���ļ���
* ����α���ļ���
* eg: �ļ�����(Document),��ʾ��(�ĵ�)
*/
# include <io.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

// �ļ�Ȩ������
void setAttrib(char cmd[], char param[], char file[])
{
	int len = strlen(cmd) + strlen(param) + strlen(file) + 3;
	char* str = (char*)malloc(sizeof(char)* len);
	if (param == "") {
		sprintf_s(str, len, "%s %s", cmd, file);
	}
	else
	{
		sprintf_s(str, len, "%s %s %s", cmd, param, file);
	}
	system(str);
}

// �ļ�д��
bool fileWrite(char ch[], char path[])
{
	if (_access(path, 0) != -1)
	{
		setAttrib("attrib", "-A -H -R -S", path);
		remove(path);
	}

	FILE* fp;
	errno_t err;                                 //��ͬ��1
	if ((err = fopen_s(&fp, path, "w")) != 0)    //��ͬ��2
		return false;                            //��ֹ����
	for (int i = 0; i < strlen(ch); i++)
		fputc(ch[i], fp); //��������һ���ַ���д�����ݣ�
	fclose(fp);
	return true;
}

// �ļ���Ϣ
void ShellClassInfo(char FolderName[], char* LocalizedResourceName, char* IconResource)
{
	int pathLen = strlen(FolderName) + 13;
	char* path = (char*)malloc(pathLen * sizeof(char));
	sprintf_s(path, pathLen, "%s\\desktop.ini", FolderName);

	int len = 78 + strlen(LocalizedResourceName) + strlen(IconResource);
	int len1 = 57 + strlen(LocalizedResourceName);
	char* info = (char*)malloc(sizeof(char)* len);
	sprintf_s(info, len1, "[.ShellClassInfo]\nLocalizedResourceName=%s", LocalizedResourceName);
	if (strlen(IconResource) > 0) {
		strcat_s(info, strlen(info) + 29, "\nIconResource=%SystemRoot%");
		sprintf_s(info, len + 1, "%s\\system32\\%s", info, IconResource);
	}

	if (!fileWrite(info, path))
		printf("�ļ�����ʧ�ܣ��п�����Ȩ�޲��㣬��ʹ�ù���Ա���У�\n");
	else
	{
		setAttrib("attrib", "+R", FolderName);
		//setAttrib("attrib", "+A +H +R +S", path);
		setAttrib("attrib", "+A +H +S", path);
	}
}

void help(char name[])
{
	printf("--------------------------------------------------------------------------------------\n| Version:\tv1.0\n| Author:\t������¶\n| ����:\t\t����α��ͼ���ļ���\n| ����:\t\t2022��1��25��10:27:44\n--------------------------------------------------------------------------------------\n\n");
	printf("����α��ͼ���ļ��еİ���\n\n");
	printf("ʾ����\n\t%s �ļ������� [��ʾ����] [ͼ������[, ͼ�����]]\n\t%s Document [�ĵ�]\n\t%s Document [�ĵ�] [SHELL32.dll, 299]\n\n", name, name, name);
	printf("Ĭ��ֵ��\n\t��ʾ����\tĬ��Ϊ�ļ�������\n\tĬ��ͼ��\t\n\n");
	printf("���磺\n\t%s Document\t\t\t��ʾΪ\"Document\" + Ĭ��ͼ��\n\t%s Document �ĵ�\t\t��ʾΪ\"�ĵ�\" + Ĭ��ͼ��\n\t%s Document �ĵ� �Զ���ͼ��\t��ʾΪ\"�ĵ�\" + \"�Զ���ͼ��\"\n\n", name, name, name);
	printf("����������������������������������������������������\n");
	printf("�� Ĭ��ͼ��Ϊ��\n�� Windowsϵͳͼ���ļ�������\n�� �ֱ���\"imageres.dll\"��\"SHELL32.dll\"\n�� ������ͼ���ļ���\"C:Windows/system32\"����\n�� �µ�ͼ����ԴҲ����\"C:Windows/system32\"����(eg:%s Document [�ĵ�] [��ͼ������])\n�� ������dll�ļ���Ҳ������ico�ļ��ȡ�����\n", name);
}

int main(int argc, char* argv[])
{
	if (argc == 2 || argc == 3 || argc == 4)
	{
		char* IconResource;
		char* LocalizedResourceName;

		if (argc == 2)
			LocalizedResourceName = argv[1];
		else
			LocalizedResourceName = argv[2];
		if (argc == 4)
			IconResource = argv[3];
		else
			IconResource = "";

		mkdir(argv[1]);
		if (!(_access(argv[1], 0) != -1))
		{
			mkdir(argv[1]);
		}
		ShellClassInfo(argv[1], LocalizedResourceName, IconResource);
	}
	else
	{
		help(argv[0]);
	}
	return 0;
}