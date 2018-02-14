int main(){
	int a[5] = {1, 20, 3, 4, 5};
	int max_val;
	max_val = a[0];		//initializing max_val
	int i;		
	for (i=0; i<5; i++){	
		if (a[i] > max_val){
			max_val=a[i];
		}
	}
}
