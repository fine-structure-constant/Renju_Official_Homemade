#include "decision.h"
#include<utility>           //pair依赖，有些头文件也包含这个，但这里需要申明
using namespace std;
// Define all your variables and functions for decision making here
int board[BOARD_SIZE][BOARD_SIZE]={0};   //棋盘黑1白2,0为空位,执黑为0，执白为1,rd为轮数S
static pair<int,int> way[]={{1,1},{1,-1},{0,1},{1,0}};
static int player,anti,tx,ty,valve_attack,valve_block,mm,rd;
static Point p0,p,tp;              //p0为落子考虑点，p用作遍历辅助,tp临时变量。
bool nearby(Point p0){      //附近两格范围内是否有子
    for(auto it : way) {
        p = p0+it;
        if(!p.spill()&&p(board)!=0) return 1;
        p = p+it;
        if(!p.spill()&&p(board)!=0) return 1;
        p = p0-it;
        if(!p.spill()&&p(board)!=0) return 1;
        p = p-it;
        if(!p.spill()&&p(board)!=0) return 1;
    }
    return 0;
}
int pos_value(int i,int j){              //边界初始化在开始时保证位置偏中部
    int tv = i+j;
    tv=tv>BOARD_SIZE-i-1+j?BOARD_SIZE-i-1+j:tv;
    tv=tv>BOARD_SIZE-j-1+i?BOARD_SIZE-j-1+i:tv;
    tv=tv>BOARD_SIZE*2-j-i-2?BOARD_SIZE*2-j-i-2:tv;
    return tv;
}
bool judge(Point tp){            //判断胜负
    if(tp(board)==0) return 0;
    int aim=p0(board);
    for(auto it :way) {
        p=tp;
        int count = -1;
        while(!p.spill() && p(board)==aim) {
            count +=1;
            p=p+it;
        }
        p=tp;
        while(!p.spill() && p(board)==aim) {
            count +=1;
            p=p-it;
        }
        if (count>=5) return 1;
    }
    return 0;
}
int mark_value() {                                           //会根据p0落子计算连子分数，同时修改ban的状态

    int danhuo3=0,tiaohuo3=0,mian3=0,huo4=0,chong4=0,tiao4=0,cheng5=0,huo2=0,chang = 0;      //huo2处理较随意
    int start,skip,value,countc=0,counts=0,huo = 0;      //countc数子，counts数总空位。
    int oth = 3-p0(board);
    for(auto it : way) {                           //统计那些变量
        countc = 0;
        counts = 0;
        skip = 0;
        huo = 1;
        p=p0;
        for(start = 0;start<4 && !p.spill() && p(board)!=oth ;start++) p=p-it;
        if(p.spill()||p(board)==oth) {
            
            p=p+it;
            //printf("[%d,%d,%d,%d______]",p0.x,p0.y,p.x,p.y);
            start--;
            huo = 0;
        } 
        start+=5;
        //printf("[%d]",start);
        for(int j =0;j<start &&!p.spill()&&p(board)!=oth;j++,p=p+it){    
            //printf("[%d,%d]",p.x,p.y);    
            counts++;
            if(p(board)==p0(board)) countc++;
            
            if(p(board)==0 && counts == 1) huo =1;         
            if(p(board)==0 && countc!=0) skip ++;
            if(skip==1 && p(board)==0) {
                if(countc ==5) cheng5++;
                else if(countc>5) chang++;
                else if(huo && countc==3) {
                    tp=p+it;
                    if(!tp.spill() && tp(board)==0) danhuo3++;
                }
                else if(!huo && countc ==3 ) {
                    tp=p+it;
                    if(!tp.spill() && tp(board)==0) mian3++;
                }
                else if(!huo && countc ==4) chong4++;
                else if(huo && countc==4) huo4++;
                else if(countc == 2) huo2++;
            }
            if(skip==2){
                countc =0;
                counts=0;
                huo=1;
                skip = 0;
            }
            if(skip == 1 && p(board)==p0(board)) {
                if(huo && countc==3) {
                    tp=p+it;
                    if(!tp.spill() && tp(board)==0) tiaohuo3++;
                    else mian3++;
                }
                if(!huo && countc ==3) {
                    tp=p+it;
                    if(!tp.spill() && tp(board)==0) mian3++;
                }
                if(countc==4){
                    tiao4++;
                }
            }

        }
        if(p.spill()||p(board)==oth) {
            if(countc== 5 ) cheng5++;
            if(countc>5) chang++;
            if (countc ==4 && skip ==0&& huo) chong4++;
        }                                                            //对于非关键如眠3，不必重复减去。
    }
    value = cheng5*5000000+huo4*160000+chong4*9000+tiao4*7000+danhuo3*10000+tiaohuo3*6000+mian3*500+huo2*50;     //打分表（己方）
    value+=pos_value(p0.x,p0.y);
    if(danhuo3+tiaohuo3+chong4>1) value+=40000;
    if(rd%2 ==0 &&(danhuo3+tiaohuo3 >1 ||huo4+chong4+tiao4>1|| chang>1)) value = -1;      //禁手
    return value;
}
bool regulate_player(Point pi){                             //专门写了个针对玩家是否禁手的，效率比mark_value略高
    p0=pi;
    int three=0,four=0;      //huo2处理较随意
    int start,skip,value,countc=0,counts=0,huo = 0;      //countc数子，counts数总空位。
    int oth = 3-p0(board);
    for(auto it : way) {                           //统计那些变量
        countc = 0;
        counts = 0;
        skip = 0;
        huo = 1;
        p=p0;
        for(start = 0;start<4 && !p.spill() && p(board)!=oth ;start++) p=p-it;
        if(p.spill()||p(board)==oth) {
            p=p+it;
            start--;
            huo = 0;
        } 
        start+=5;
        for(int j =0;j<start &&!p.spill()&&p(board)!=oth;j++,p=p+it){     
            counts++;
            if(p(board)==p0(board)) countc++;
            if(p(board)==0 && counts == 1) huo =1;         
            if(p(board)==0 && countc!=0) skip ++;
            if(skip==1 && p(board)==0) {
                if(countc>5) return 1;
                else if(huo && countc==3) {
                    tp=p+it;
                    if(!tp.spill() && tp(board)==0) three++;
                }
                else if(countc ==4) four++;
            }
            if(skip==2){
                countc =0;
                counts=0;
                huo=1;
                skip = 0;
            }
            if(skip == 1 && p(board)==p0(board)) {
                if(huo && countc==3) {
                    tp=p+it;
                    if(!tp.spill() && tp(board)==0) three++;
                }
                if(countc==4){
                    four++;
                }
            }
        }
        if(p.spill()||p(board)==oth) {
            if(countc>5) return 1;
            if (countc ==4 && skip ==0&& huo) four++;
        }                                                            //对于非关键如眠3，不必重复减去。
    }
    if(three >1 ||four>1) return 1;      //禁手
    return 0;
}
inline int covalue() {
    p0(board)= anti+1;
    valve_attack=mark_value();
    p0(board) =player+1;
    valve_block=mark_value();
    p0(board)=0;
    return valve_attack+valve_block/2;
}
int MM(int depth, int alpha, int beta, int turn) {  // alpha < beta
    if (depth <= 0) {  // Base case, ensure it's a max node when depth%2 == 0
        int mx = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                p0.set(i, j);
                if (p0(board) != 0) continue;  // Skip if already occupied
                int mm = covalue();  // Evaluate the current board state
                if (mm > mx) {
                    mx = mm;
                    tx = p0.x;
                    ty = p0.y;
                }
            }
        }
        return mx;
    }
    
    if (depth % 2 == 1) {  // Min node (minimizing the score)
        beta = 0x7FFFFFFF;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                p0.set(i, j);
                if (p0(board) != 0 || !nearby(p0)) continue; 
                p0(board) = turn + 1;
                int mm = MM(depth - 1, alpha, beta, 1 - turn);  
                p0.set(i, j);
                p0(board) = 0;

                if (mm < beta) {
                    tx = p0.x;
                    ty = p0.y;
                    beta = mm;
                }
                //if (alpha >= beta) break;  
            }
        }
        return beta;
    } else {  
        alpha = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                p0.set(i, j);
                if (p0(board) != 0 || !nearby(p0)) continue;  
                p0(board) = turn + 1;
                int mm = MM(depth - 1, alpha, beta, 1 - turn);  
                p0.set(i, j);
                p0(board) = 0;

                if (mm > alpha) {
                    alpha = mm;
                    tx = p0.x;
                    ty = p0.y;
                }
                //if (alpha >= beta) break;// Alpha cut-off         也没太搞明白这里的细节。
            }
        }
        return alpha;
    }
}
Point decision_shell(int whom,int r){
    anti =whom;
    player = 1-whom;
    rd = r;
    if (MM(0, 0, 0, anti) < 50000 && rd > 5) MM(MAX_DEPTH, 0, 0x7FFFFFFF, anti);
    p0.set(tx,ty);
    return p0;
}