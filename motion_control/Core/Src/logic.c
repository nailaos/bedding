#include "logic.h"
#include "usart.h"
#include <stdlib.h>

#define SPE 20
Position_edc25 Base;
Position_edc25 my_pos;
Position_edc25 target;
Position_edc25 path[50];
int pathlen = 0;
int myMap_new[64] = {0};

int getMapId_new(Position_edc25* points) {
    int x = (int)points->posx;
    int y = (int)points->posy;
    return 8 * y + x;
}
int getdir_new(Position_edc25* from, Position_edc25* to) {
    if (Base.posx == 0.5) {
        if ((from->posx - to->posx) > 0.3||to->posx-from->posx>0.3) {
            if (to->posx < from->posx)
                return 5;
            else

                return 4;
        } else {
        	if (to->posy > from->posy)
        	    return 0;
        	else
        	    return 1;

        }
    }
    else {
        if ((from->posx - to->posx) > 0.5||to->posx-from->posx>0.5) {
            if (to->posx < from->posx)
                return 4;
            else
                return 5;
        } else {
            if (to->posy > from->posy)
                return 1;
            else
                return 0;

        }
    }
}
int mymove_new(Position_edc25* from, Position_edc25* to) {
	int flag=1;//flag为1说明可以前进
	int id = getMapId_new(to);
	Position_edc25 curr;

	if (getHeightOfId(id)==0) {
		flag=0;
		//u1_printf("id:%d,height:0\n",id);
	    if (getWoolCount() == 0)
	        return 0;
	    else{
	        place_block_id(id);
	        HAL_Delay(500);
	        //u1_printf("place\n");
	        flag=1;
	    }

	}
	if(flag){
		setdir(getdir_new(from,to));
	    setv(SPE);
		getPosition(&curr);
		//u1_printf("dir:%d,nowpos(%f，%f)\n",dir,curr.posx,curr.posy);
		if(dir==0||dir==1){
			while(abs(curr.posy-to->posy)>0.3){
				getPosition(&curr);
				//u1_printf("dir:%d,(%f,%f)\n",dir,curr.posx,curr.posy);
			}
		}
		else{
			while(abs(curr.posx-to->posx)>0.3){
				getPosition(&curr);
				//u1_printf("dir:%d,(%f,%f)\n",dir,curr.posx,curr.posy);
			}
		}
		setv(0);
		return 1;
	}
	return 0;
}
int move_target(Position_edc25 *from,Position_edc25 *to,int v){
	setdir(getdir_new(from,to));
	pidparm1.lr=0;
	pidparm1.sum=0;
	setv(v);
	if(dir==0||dir==1){
		while((my_pos.posy-to->posy)>0.3||to->posy-my_pos.posy>0.3){

			//u1_printf("dir:%d,(%f,%f)\n",dir,curr.posx,curr.posy);
		}
		u1_printf("now:(%f,%f),target:(%f,%f)",my_pos.posx,my_pos.posy,to->posx,to->posy);
	}
	else{
		while((my_pos.posx-to->posx)>0.3||to->posx-my_pos.posx>0.3){

			//u1_printf("dir:%d,(%f,%f)\n",dir,curr.posx,curr.posy);
		}
	}

	setv(0);
	return 1;
}
int InitBase(){
	Position_edc25 curr;
	getPosition(&curr);
	if(curr.posx>3){
		Base.posx=7.5;
		Base.posy=7.5;
		return 1;
	}
	else{
		Base.posx=0.5;
		Base.posy=0.5;
		return 0;
	}
}
int move_home(){
	if(Base.posx==7.5){//家在右下角的情况   //假设嵌套函数不会出现太多问题，实在不行就复制出来
		Position_edc25 knee ;

	}
	else{//家在左上角的情况

	}
}
void gohome() {
	pathlen = 3;
	path[0].posy = my_pos.posy;
	path[0].posx = Base.posx;
	path[1] = Base;
	path[2] = Base;
	//move_target();
}

int make_choice(){
	if(Base.posx == 0.5) {
		pathlen = 15;
		path[0].posx = 0.5;
		path[0].posy = 1.5;
		path[1].posx = 0.5;
		path[1].posy = 2.5;
		path[2].posx = 0.5;
		path[2].posy = 3.5;
		path[3].posx = 0.5;
		path[3].posy = 4.5;
		path[4].posx = 0.5;
		path[4].posy = 5.5;
		path[5].posx = 0.5;
		path[5].posy = 6.5;
		path[6].posx = 0.5;
		path[6].posy = 7.5;
		path[7].posx = 0.5;
		path[7].posy = 6.5;
		path[8].posx = 0.5;
		path[8].posy = 5.5;
		path[9].posx = 0.5;
		path[9].posy = 4.5;
		path[10].posx = 0.5;
		path[10].posy = 3.5;
		path[11].posx = 0.5;
		path[11].posy = 2.5;
		path[12].posx = 0.5;
		path[12].posy = 1.5;
		path[13].posx = 0.5;
		path[13].posy = 0.5;
		path[14].posx = 0.5;
		path[14].posy = 0.5;
		return 1;
	} else {
		pathlen = 15;
		path[0].posx = 7.5;
		path[0].posy = 6.5;
		path[1].posx = 7.5;
		path[1].posy = 5.5;
		path[2].posx = 7.5;
		path[2].posy = 4.5;
		path[3].posx = 7.5;
		path[3].posy = 3.5;
		path[4].posx = 7.5;
		path[4].posy = 2.5;
		path[5].posx = 7.5;
		path[5].posy = 1.5;
		path[6].posx = 7.5;
		path[6].posy = 0.5;
		path[7].posx = 7.5;
		path[7].posy = 1.5;
		path[8].posx = 7.5;
		path[8].posy = 2.5;
		path[9].posx = 7.5;
		path[9].posy = 3.5;
		path[10].posx = 7.5;
		path[10].posy = 4.5;
		path[11].posx = 7.5;
		path[11].posy = 5.5;
		path[12].posx = 7.5;
		path[12].posy = 6.5;
		path[13].posx = 7.5;
		path[13].posy = 7.5;
		path[14].posx = 7.5;
		path[14].posy = 7.5;
		return 1;
	}
	if(Base.posx==0.5){
		if(pathlen==0){
			pathlen = 10;
			path[0].posx = 0.5;
			path[0].posy = 1.5;
			path[1].posx = 0.5;
			path[1].posy = 2.5;
			path[2].posx = 1.5;
			path[2].posy = 2.5;
			path[3].posx = 2.5;
			path[3].posy = 2.5;
			path[4].posx = 2.5;
			path[4].posy = 1.5;
			path[5].posx = 2.5;
			path[5].posy = 0.5;
			path[6].posx = 1.5;
			path[6].posy = 0.5;
			path[7].posx = 1.5;
			path[7].posy = 1.5;
			path[8].posx = 0.5;
			path[8].posy = 1.5;
			path[9].posx = 0.5;
			path[9].posy = 0.5;
			return 1;
		}
		if(getWoolCount()>15){
			pathlen = 24;
			path[0].posx = 8-7.5;
			path[0].posy = 8-6.5;
			path[1].posx = 8-7.5;
			path[1].posy = 8-5.5;
			path[2].posx = 8-7.5;
			path[2].posy = 8-4.5;
			path[3].posx = 8-7.5;
			path[3].posy = 8-3.5;
			path[4].posx = 8-6.5;
			path[4].posy = 8-3.5;
			path[5].posx = 8-5.5;
			path[5].posy = 8-3.5;
			path[6].posx = 8-4.5;
			path[6].posy = 8-3.5;
			path[7].posx = 8-3.5;
			path[7].posy = 8-3.5;
			path[8].posx = 8-3.5;
			path[8].posy = 8-4.5;
			path[9].posx = 8-3.5;
			path[9].posy = 8-5.5;
			path[10].posx = 8-3.5;
			path[10].posy = 8-6.5;
			path[11].posx = 8-4.5;
			path[11].posy = 8-6.5;
			path[12].posx = 8-4.5;
			path[12].posy = 8-5.5;
			path[13].posx = 8-4.5;
			path[13].posy = 8-4.5;
			path[14].posx = 8-5.5;
			path[14].posy = 8-4.5;
			path[15].posx = 8-5.5;
			path[15].posy = 8-5.5;
			path[16].posx = 8-5.5;
			path[16].posy = 8-6.5;
			path[17].posx = 8-6.5;
			path[17].posy = 8-6.5;
			path[18].posx = 8-6.5;
			path[18].posy = 8-5.5;
			path[19].posx = 8-6.5;
			path[19].posy = 8-4.5;
			path[20].posx = 8-7.5;
			path[20].posy = 8-4.5;
			path[21].posx = 8-7.5;
			path[21].posy = 8-5.5;
			path[22].posx = 8-7.5;
			path[22].posy = 8-6.5;
			path[23].posx = 8-7.5;
			path[23].posy = 8-7.5;
		}
		if(getWoolCount() > 10) {
			pathlen = 16;
			path[0].posx = 0.5;
			path[0].posy = 1.5;
			path[1].posx = 0.5;
			path[1].posy = 2.5;
			path[2].posx = 0.5;
			path[2].posy = 3.5;
			path[3].posx = 0.5;
			path[3].posy = 4.5;
			path[4].posx = 1.5;
			path[4].posy = 4.5;
			path[5].posx = 2.5;
			path[5].posy = 4.5;
			path[6].posx = 3.5;
			path[6].posy = 4.5;
			path[7].posx = 4.5;
			path[7].posy = 4.5;
			path[8].posx = 4.5;
			path[8].posy = 3.5;
			path[9].posx = 4.5;
			path[9].posy = 2.5;
			path[10].posx = 4.5;
			path[10].posy = 1.5;
			path[11].posx = 3.5;
			path[11].posy = 1.5;
			path[12].posx = 2.5;
			path[12].posy = 1.5;
			path[13].posx = 1.5;
			path[13].posy = 1.5;
			path[14].posx = 0.5;
			path[14].posy = 1.5;
			path[15].posx = 0.5;
			path[15].posy = 0.5;
			return 3;
		}
		if(getWoolCount() > 7) {
			pathlen = 12;
			path[0].posx = 0.5;
			path[0].posy = 1.5;
			path[1].posx = 0.5;
			path[1].posy = 2.5;
			path[2].posx = 0.5;
			path[2].posy = 3.5;
			path[3].posx = 1.5;
			path[3].posy = 3.5;
			path[4].posx = 2.5;
			path[4].posy = 3.5;
			path[5].posx = 3.5;
			path[5].posy = 3.5;
			path[6].posx = 3.5;
			path[6].posy = 2.5;
			path[7].posx = 3.5;
			path[7].posy = 1.5;
			path[8].posx = 2.5;
			path[8].posy = 1.5;
			path[9].posx = 1.5;
			path[9].posy = 1.5;
			path[10].posx = 0.5;
			path[10].posy = 1.5;
			path[11].posx = 0.5;
			path[11].posy = 0.5;
			return 2;
		}
	}
	else{
		if(pathlen==0){
			pathlen = 10;
			path[0].posx = 7.5;
			path[0].posy = 6.5;
			path[1].posx = 7.5;
			path[1].posy = 5.5;
			path[2].posx = 6.5;
			path[2].posy = 5.5;
			path[3].posx = 5.5;
			path[3].posy = 5.5;
			path[4].posx = 5.5;
			path[4].posy = 6.5;
			path[5].posx = 5.5;
			path[5].posy = 7.5;
			path[6].posx = 6.5;
			path[6].posy = 7.5;
			path[7].posx = 6.5;
			path[7].posy = 6.5;
			path[8].posx = 7.5;
			path[8].posy = 6.5;
			path[9].posx = 7.5;
			path[9].posy = 7.5;
			return 1;
		}
		if(getWoolCount() > 15){
			pathlen = 24;
			path[0].posx = 7.5;
			path[0].posy = 6.5;
			path[1].posx = 7.5;
			path[1].posy = 5.5;
			path[2].posx = 7.5;
			path[2].posy = 4.5;
			path[3].posx = 7.5;
			path[3].posy = 3.5;
			path[4].posx = 6.5;
			path[4].posy = 3.5;
			path[5].posx = 5.5;
			path[5].posy = 3.5;
			path[6].posx = 4.5;
			path[6].posy = 3.5;
			path[7].posx = 3.5;
			path[7].posy = 3.5;
			path[8].posx = 3.5;
			path[8].posy = 4.5;
			path[9].posx = 3.5;
			path[9].posy = 5.5;
			path[10].posx = 3.5;
			path[10].posy = 6.5;
			path[11].posx = 4.5;
			path[11].posy = 6.5;
			path[12].posx = 4.5;
			path[12].posy = 5.5;
			path[13].posx = 4.5;
			path[13].posy = 4.5;
			path[14].posx = 5.5;
			path[14].posy = 4.5;
			path[15].posx = 5.5;
			path[15].posy = 5.5;
			path[16].posx = 5.5;
			path[16].posy = 6.5;
			path[17].posx = 6.5;
			path[17].posy = 6.5;
			path[18].posx = 6.5;
			path[18].posy = 5.5;
			path[19].posx = 6.5;
			path[19].posy = 4.5;
			path[20].posx = 7.5;
			path[20].posy = 4.5;
			path[21].posx = 7.5;
			path[21].posy = 5.5;
			path[22].posx = 7.5;
			path[22].posy = 6.5;
			path[23].posx = 7.5;
			path[23].posy = 7.5;

			return 4;
		}
		if(getWoolCount() > 10) {
			pathlen = 16;
			path[0].posx = 7.5;
			path[0].posy = 6.5;
			path[1].posx = 7.5;
			path[1].posy = 5.5;
			path[2].posx = 7.5;
			path[2].posy = 4.5;
			path[3].posx = 7.5;
			path[3].posy = 3.5;
			path[4].posx = 6.5;
			path[4].posy = 3.5;
			path[5].posx = 5.5;
			path[5].posy = 3.5;
			path[6].posx = 4.5;
			path[6].posy = 3.5;
			path[7].posx = 3.5;
			path[7].posy = 3.5;
			path[8].posx = 3.5;
			path[8].posy = 4.5;
			path[9].posx = 3.5;
			path[9].posy = 5.5;
			path[10].posx = 3.5;
			path[10].posy = 6.5;
			path[11].posx = 4.5;
			path[11].posy = 6.5;
			path[12].posx = 5.5;
			path[12].posy = 6.5;
			path[13].posx = 6.5;
			path[13].posy = 6.5;
			path[14].posx = 7.5;
			path[14].posy = 6.5;
			path[15].posx = 7.5;
			path[15].posy = 7.5;
			return 3;
		}
		if(getWoolCount() > 7) {
			pathlen = 12;
			path[0].posx = 7.5;
			path[0].posy = 6.5;
			path[1].posx = 7.5;
			path[1].posy = 5.5;
			path[2].posx = 7.5;
			path[2].posy = 4.5;
			path[3].posx = 6.5;
			path[3].posy = 4.5;
			path[4].posx = 5.5;
			path[4].posy = 4.5;
			path[5].posx = 4.5;
			path[5].posy = 4.5;
			path[6].posx = 4.5;
			path[6].posy = 5.5;
			path[7].posx = 4.5;
			path[7].posy = 6.5;
			path[8].posx = 5.5;
			path[8].posy = 6.5;
			path[9].posx = 6.5;
			path[9].posy = 6.5;
			path[10].posx = 7.5;
			path[10].posy = 6.5;
			path[11].posx = 7.5;
			path[11].posy = 7.5;
			return 2;
		}
	}

}
int Trade(){
	int myEmraldCount = getEmeraldCount();
	int myWoolCount = getWoolCount();
	while(myWoolCount <4
			&& myEmraldCount>2){
		trade_id(3);
		HAL_Delay(200);
		myEmraldCount-=2;
		myWoolCount+=1;
	}
	while(myEmraldCount>=32){
		trade_id(1);
		HAL_Delay(200);
		myEmraldCount-=32;
	}
	return 1;
}
