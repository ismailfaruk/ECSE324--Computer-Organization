extern int MAX_2(int x, int y);

int main(){
    int a[5] = {1, 20, 3, 4, 5};
    int max_val;
	max_val = a[0];
    int i;
    for (i=1; i<5; i++){
        max_val = MAX_2(max_val, a[i]);
    }
    return max_val;
}