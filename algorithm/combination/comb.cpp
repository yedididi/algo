#include <iostream>



void permutation(int depth){
    if(depth == r){
        printArray(pArr);
        return;
    }
    
    for(int i = 1; i <= n; i++){
        if(!check[i]){
            check[i] = true;
            pArr[depth] = i;
            permutation(depth + 1);
            check[i] = false;
        }
    }
}

void combination(int depth, int next){
    if(depth == r){
        printArray(cArr);
        return;
    }

    for(int i = next; i <= n; i++){
        cArr[depth] = i;
        combination(depth + 1, i + 1);
    }
}