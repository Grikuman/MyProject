rem FBXのフォルダ
set FBX=..\FBX

rem CMOの出力フォルダ
set CMO=..\CMO

rem EXEの実行
CmoPathCut.exe /f %FBX% /c %CMO%

rem このバッチファイルをビルドイベントに組み込まない！
rem →ddsファイルの名前が長くなるので…
