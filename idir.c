/**
* 创建图标文件夹
* 创建伪名文件夹
* eg: 文件夹名(Document),显示名(文档)
*/
# include <io.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

// 文件权限设置
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

// 文件写入
bool fileWrite(char ch[], char path[])
{
	if (_access(path, 0) != -1)
	{
		setAttrib("attrib", "-A -H -R -S", path);
		remove(path);
	}

	FILE* fp;
	errno_t err;                                 //不同点1
	if ((err = fopen_s(&fp, path, "w")) != 0)    //不同点2
		return false;                            //终止程序
	for (int i = 0; i < strlen(ch); i++)
		fputc(ch[i], fp); //向磁盘输出一个字符（写入数据）
	fclose(fp);
	return true;
}

// 文件信息
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
		printf("文件创建失败，有可能是权限不足，请使用管理员运行！\n");
	else
	{
		setAttrib("attrib", "+R", FolderName);
		//setAttrib("attrib", "+A +H +R +S", path);
		setAttrib("attrib", "+A +H +S", path);
	}
}

void help(char name[])
{
	printf("--------------------------------------------------------------------------------------\n| Version:\tv1.0\n| Author:\t晴天雨露\n| 程序:\t\t创建伪名图标文件夹\n| 日期:\t\t2022年1月25日10:27:44\n--------------------------------------------------------------------------------------\n\n");
	printf("创建伪名图标文件夹的帮助\n\n");
	printf("示例：\n\t%s 文件夹名称 [显示名称] [图标名称[, 图标参数]]\n\t%s Document [文档]\n\t%s Document [文档] [SHELL32.dll, 299]\n\n", name, name, name);
	printf("默认值：\n\t显示名称\t默认为文件夹名称\n\t默认图标\t\n\n");
	printf("例如：\n\t%s Document\t\t\t显示为\"Document\" + 默认图标\n\t%s Document 文档\t\t显示为\"文档\" + 默认图标\n\t%s Document 文档 自定义图标\t显示为\"文档\" + \"自定义图标\"\n\n", name, name, name);
	printf("——————————————————————————\n");
	printf("● 默认图标为空\n● Windows系统图标文件有两个\n● 分别是\"imageres.dll\"和\"SHELL32.dll\"\n● 这两个图标文件在\"C:Windows/system32\"下面\n● 新的图标资源也放在\"C:Windows/system32\"下面(eg:%s Document [文档] [新图标名称])\n● 可以是dll文件，也可以是ico文件等。。。\n", name);
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