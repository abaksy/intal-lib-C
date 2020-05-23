#include<string.h>
#include<stdlib.h>
#include<stdio.h>

static int min(int a, int b)
{
	return a<b?a:b;
}

static int length(const char* str)
{
	int i = 0;
	while(str[i]!='\0')
		i++;
	return i;
}

static char* strip_zeros(char* str)
{
	int m = length(str);
	int i;
	for(i=0; i<m; ++i)
	{
		if(str[i]!='0')
			break;
	}
	for(int j = i; j<m; ++j)	
		str[j-i] = str[j];
	str[m-i] = '\0';
	return str;
}

char* intal_add(const char* intal1, const char* intal2)
{
	if(strcmp(intal1, "0")==0 && strcmp(intal2, "0")==0)
	{
		char* res = malloc(sizeof(char)*2);
		strcpy(res, "0");
		return res;
	}
	int m = length(intal1), n = length(intal2);
	int maxlen = m>n?m:n;
	char* result = (char*)malloc(sizeof(char)*(maxlen+2));
	for(int i=0; i<maxlen+2; ++i)
		result[i]='0';
	result[maxlen+1]='\0';
	int k = maxlen, carry = 0, temp, i, j;
	for(i = m-1, j = n-1; i >= 0 && j >= 0; --i, --j)
	{
		temp = (intal1[i]-'0')+(intal2[j]-'0')+carry;
		result[k--] = (char)(temp%10+'0');
		carry = temp/10;
	}
	if(i==-1&&j!=-1)
	{
		while(k!=0)
		{
			temp = (intal2[j--]-'0') + carry;
			result[k--] = (char)(temp%10+'0');
			carry = temp/10;
		}
	}
	else if(j==-1 && i!=-1)
	{
		while(k!=0)
		{
			temp = (intal1[i--]-'0') + carry;
			result[k--] = (char)(temp%10+'0');
			carry = temp/10;
		}
	}
	if(carry!=0)
		result[0]=((result[0]-'0')+carry)+'0';
	result = strip_zeros(result);
	return result;
}

int intal_compare(const char* intal1, const char* intal2)
{
	int m=length(intal1), n=length(intal2);
	if(m>n)
		return 1;
	else if(n>m)
		return -1;
	else
	{
		for(int i=0; i<m; i++)
		{
			if(intal1[i] > intal2[i])
				return 1;
			else if(intal1[i] < intal2[i])
				return -1;
		}
		return 0;
	}
}

char* intal_diff(const char* intal1, const char* intal2)
{
	char* diff=malloc(2*sizeof(char));
	strcpy(diff, "0");
	int m = length(intal1), n = length(intal2);
	int maxlen = m>n?m:n;
	int k = maxlen-1;
	int comp = intal_compare(intal1, intal2);
	if(comp==0)
		return diff;
	free(diff);
	char* result = malloc(sizeof(int)*(maxlen+1));
	char* i1=malloc(m*sizeof(char));
	char* i2 = malloc(n*sizeof(char));
	strcpy(i1, intal1);
	strcpy(i2, intal2);
	result[maxlen]='\0';
	if(comp==1) //intal1 > intal2
	{	
		int i, j;
		for(i=m-1, j=n-1; i>=0 && j>=0; --i, --j)
		{
			if(i1[i] >= i2[j])
				result[k--] = i1[i] - i2[j] + '0';
			else
			{
				if(i1[i-1]!='0') 
					i1[i-1]-=1;
				else
				{
					int key=i-1;
					while(i1[key]=='0')
					{
						i1[key]='9';
						key--;
					}
					i1[key]-=1;
				}
				result[k--] = (10 + (i1[i]-'0')) - (i2[j] -'0') + '0';
			}
		}
		if(i!=-1)
		{
			for(int k=i; k>=0; k--)
				result[k] = i1[k];
		}
		free(i1);
		free(i2);
		result = strip_zeros(result);
		return result;
	}
	else //intal2 > intal1
	{
		int i, j;
		for(i=n-1, j=m-1; i>=0 && j>=0; --i, --j)
		{
			if(i2[i] >= i1[j])
				result[k--] = i2[i] - i1[j] + '0';
			else
			{
				if(i2[i-1]!='0') 
					i2[i-1]-=1;
				else
				{
					int key=i-1;
					while(i2[key]=='0')
					{
						i2[key]='9';
						key--;
					}
					i2[key]-=1;
				}
				result[k--] = (10 + (i2[i]-'0')) - (i1[j] -'0') + '0';
			}
		}
		if(i!=-1)
		{
			for(int k=i; k>=0; k--)
				result[k] = i2[k];
		}
		free(i1);
		free(i2);
		result = strip_zeros(result);
		return result;
	}
}

char* intal_multiply(const char* intal1, const char* intal2)
{
	if(strcmp(intal1, "0")==0 || strcmp(intal2, "0")==0)
	{
		char* res = malloc(sizeof(char)*2);
		strcpy(res, "0");
		return res;
	}
	char* temp = malloc(sizeof(char)*1001);
	int m = length(intal1), n = length(intal2);
	char* result = malloc(sizeof(char)*(m+n+1));
	for(int i=0; i<1000; ++i)
		temp[i]='0';
	temp[1000]='\0';
	strcpy(result, "0");
	int k = m+n-1, carry=0;
	for(int i=n-1; i>=0; --i)
	{
		k = m;
		for(int j=m-1; j>=0; --j)
		{
			int v = (intal1[j]-'0')*(intal2[i]-'0')+carry;
			temp[k+i] = (char)(v%10 + '0');
			k--;
			carry = v/10;
		}
		temp[i] = carry+'0';
		temp[m+n] = '\0';
		char* ss = intal_add(result, temp);
		strcpy(result, ss);
		free(ss);
		for(int i=0; i<1001; ++i)
			temp[i]='0';
		carry=0;
	}
	free(temp);
	return result;
}

static char* sub(char* intal1,char* intal2)
{
	char* mod=intal2;
	char* a;
	char* s=(char*)malloc(sizeof(char)*1001);
	strcpy(s,intal1);
	while(intal_compare(s,mod)!=-1)
	{						
		a=intal_diff(s,mod);
		strcpy(s,a);
		free(a);		
	}
	return s;
}

char* intal_mod(const char* intal1, const char* intal2)
{
	char* t2=(char*)malloc(sizeof(char)*1001);
	char* t1=(char*)malloc(sizeof(char)*1001);
	strcpy(t1,intal1);		
	strcpy(t2,intal2);
	char* result=(char*)malloc(sizeof(char)*1001);	
	strcpy(result, "0");	
	if(strcmp(intal1,"0")==0)
	{
		free(t1);
		free(t2);
	    return result;
	}
	char *p,*q;
	int m = strlen(intal1);
	for(int i=0;i<m;i++)	
	{	
		char* i1=(char*)malloc(sizeof(char)*1001);
		char* i2=(char*)malloc(sizeof(char)*1001);
		char* t=(char*)malloc(sizeof(char)*2);
		t[0]=intal1[i];		
		t[1]='\0';
		strcpy(i1, result);			
		if(strcmp(i1, "0")!=0)
			strcat(i1,"0");			
		p=intal_add(i1, t);
		strcpy(i2, p);
		q=sub(i2, t2);
		strcpy(result, q);
		free(p);
		free(q);
		free(i1);
		free(i2);
		free(t);
		if(strcmp(result, t2)==0)
			strcpy(result,"0");
	}
	free(t1);	
	free(t2);	
	return result;	
}

char* intal_pow(const char* intal1, unsigned int n)
{
    char* res = malloc(sizeof(char)*1001);
	char* x = malloc(sizeof(char)*1001);
	char* temp;
	res[1000] = '\0';
	x[1000] = '\0';
	strcpy(x, intal1);
	strcpy(res, "1");
    while (n > 0) { 
        if (n & 1)  
        {
			temp = intal_multiply(res, x);
			strcpy(res, temp);
			free(temp);
		}
        n = n >> 1;
		if(n!=0)
		{
			temp = intal_multiply(x, x);
			strcpy(x, temp);
			free(temp);
		}
    } 
	free(x);
	return res;
} 

char* intal_gcd(const char* intal1, const char* intal2)
{	
	if(strcmp(intal1, "0")==0 && strcmp(intal2,"0")==0)
	{
		char* temp = malloc(sizeof(char)*2);
		strcpy(temp, "0");
		return temp;
	}
	char* i1=(char*)malloc(sizeof(char)*1001);
	char* i2=(char*)malloc(sizeof(char)*1001);
  	strcpy(i1,intal1);
	strcpy(i2,intal2);	
	char* a;
	while(!strcmp(i2,"0")==0)
	{
		a=intal_mod(i1,i2);	
		strcpy(i1,i2);		
		strcpy(i2,a);		
		free(a);	
	}
	free(i2);
	return i1;
}


char* intal_fibonacci(unsigned int n)
{
	char* a = malloc(sizeof(char)*1001);
	char* b = malloc(sizeof(char)*1001);
	strcpy(a, "0");
	strcpy(b, "1");
	if(n==0)
	{
		free(b);
		return a;
	}
	else if(n==1)
	{
		free(a);
		return b;
	}
	char* result;
	char* final = malloc(sizeof(char)*1001);
	for(int i=2;i<=n;++i)
	{
		result = intal_add(a, b);
		strcpy(a, b);
		strcpy(b, result);
		free(result);
	}
	strcpy(final, b);	 
	free(a);
	free(b);
	return final;
}

char* intal_factorial(unsigned int n)
{
	char* result = malloc(sizeof(char)*1001);
	char* counter = malloc(sizeof(char)*1001);
	strcpy(result, "1");
	strcpy(counter, "1");
	char* temp;
	char* temp1;
	if(n==1 || n==0)
	{
		return result;
	}
	for(int i=0; i<n-1; ++i)
	{
		temp = intal_add(counter, "1");
		strcpy(counter, temp);
		temp1 = intal_multiply(result, counter);
		strcpy(result, temp1);
		free(temp1);
		free(temp);
	}
	free(counter);
	return result;		
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{ 
	if(k > n-k)
		k = n-k; //nCk = nCn-k
	char** arr = (char**)malloc(sizeof(char*)*(k+1));
	for(int i=0; i<k+1; ++i)
	{
		arr[i] = malloc(sizeof(char)*1001);
		strcpy(arr[i], "0");
	}
	strcpy(arr[0], "1"); // nC0 is 1 
	char* temp;
	for (int i=1; i<=n; i++) 
	{
		for (int j = min(i, k); j > 0; j--) 
		{
			temp = intal_add(arr[j], arr[j-1]); 
			if(intal_compare(temp, "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")==-1)
			{
				strcpy(arr[j], temp);
				free(temp);
			}
		}
	}
	char* final = malloc(sizeof(char)*1000);
	strcpy(final, arr[k]);
	//printf("final = %s\n", final);
	for(int i=0; i<k+1;++i)
		free(arr[i]);
	free(arr);
	return final;
} 

int intal_max(char **arr, int n)
{
	char* max_intal = malloc(sizeof(char)*1001);
	strcpy(max_intal, arr[0]);
	int maxindex=0;
	for(int i=1; i<n; ++i)
	{
		int l = intal_compare(max_intal, arr[i]);
		if(l==-1)
		{
			strcpy(max_intal, arr[i]);
			maxindex = i;
		}
	}
	free(max_intal);
	return maxindex;
}

int intal_min(char **arr, int n)
{
	char* min_intal = malloc(sizeof(char)*1001);
	strcpy(min_intal, arr[0]);
	int minindex=0;
	for(int i=1; i<n; ++i)
	{
		int l = intal_compare(min_intal, arr[i]);
		if(l==1)
		{
			strcpy(min_intal, arr[i]);
			minindex = i;
		}
	}
	free(min_intal);
	return minindex;
}

int intal_search(char **arr, int n, const char* key)
{
	for(int i=0; i<n; ++i)
	{
		if(strcmp(arr[i], key)==0)
			return i;
	}
	return -1;
}


int intal_binsearch(char **arr, int n, const char* key)
{
	int start = 0, end = n-1, mid, index = -1;
	while(start<=end)
	{	
		mid = (start+end)/2;
		if(intal_compare(key, arr[mid])==0)
		{
			index = mid;
			end = mid-1;
		}
		else if(intal_compare(key, arr[mid])==1)
			start = mid+1;
		else
			end = mid-1;
	}
	return index;
}

static void heapify(char** arr, int n, int i)
{
	char* temp;
	int largest = i, r = 2*i+1, l = 2*i+2;
	if(l < n && intal_compare(arr[l], arr[largest])==1)
		largest = l;
	if(r < n && intal_compare(arr[r], arr[largest])==1)
		largest = r;
	if(largest!=i)
	{
		temp = arr[largest];
		arr[largest] = arr[i]; 
		arr[i] = temp;
		heapify(arr, n, largest);
	}
}

void intal_sort(char **arr, int n)
{
	char* temp;
	for(int i=n/2-1; i>=0; --i)
		heapify(arr, n, i);
	for(int i=n-1; i>0; --i)
	{
		temp = arr[0];
		arr[0] = arr[i]; 
		arr[i] = temp;
		heapify(arr, i, 0);
	}
}

static char* max(char* intal1,char* intal2)
{
    if(intal_compare(intal1, intal2)==1)
    {
        return intal1;
    }
    else
    {
        return intal2;
    }
}

char* coin_row_problem(char **arr, int n)
{
	char *i_1, *i_2, *ans, * temp, *temp1;
	if(n==0)
	{
		char* temp = malloc(sizeof(char)*2);
		strcpy(temp, "0");
		return temp;
	}
	else if(n==1)
	{
		char* temp = malloc(sizeof(char)*1001);
		strcpy(temp, arr[0]);
		return temp;
	}
	else if(n==2)
	{
		temp = max(arr[0], arr[1]);
		return temp;
	}
	else
	{
		i_2 = malloc(sizeof(char)*1001);
		i_1 = malloc(sizeof(char)*1001);
		ans = malloc(sizeof(char)*1001);
		strcpy(i_2, "0"); //F[0] = 0
		strcpy(i_1, arr[0]); //F[1] = arr[1]
		for(int i=2; i<=n; ++i)
		{
			temp = intal_add(arr[i-1], i_2);
			temp1 = max(temp, i_1);
			strcpy(ans, temp1);
			strcpy(i_2, i_1);
			strcpy(i_1, temp1);
			free(temp);
		}
	}
	free(i_2);
	free(i_1);
	return ans;
}
