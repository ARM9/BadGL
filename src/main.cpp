#include "Precompiled.h"
#include "App.h"

int main(int argc, char * argv[]){
	if(argc > 1){
		printf("%s", argv[argc-1]);
	}
	
	App *app = new App();

	app->run();

	delete app;
	return 0;
}
