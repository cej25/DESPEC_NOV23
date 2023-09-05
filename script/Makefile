all : runScriptAna

runScriptAna : Script_Ana.C
	g++ -g `go4-config --cflags` `go4-config --glibs` -I../src -L../src -lGo4UserAnalysis -o ../runScriptAna Script_Ana.C
