#include<cstdio>
#include<vector>
using namespace std;
void pattern_matrix_input(vector<vector<int> > &Matrix)
{
    for(int i=0;i<Matrix.size();i++)
        scanf("%d",&Matrix[Matrix.size()-1][Matrix.size()-1-i]);
    for(int i=0;i<Matrix.size()-1;i++)
        Matrix[i][i+1]=1;
}
void entry_value_input(vector<vector<int> > &Matrix)
{
    for(int i=0;i<Matrix.size();i++)
        scanf("%d",&Matrix[Matrix.size()-1-i][0]);
}
void print_matrix(vector<vector<int> > &Matrix)
{
    for(int i=0;i<Matrix.size();i++)
    {
        for(int j=0;j<Matrix[0].size();j++)
            printf("%d ",Matrix[i][j]);
        printf("\n");
    }

}
void matrix_multiplication(vector<vector<int> > &Matrix_A,
                           vector<vector<int> > &Matrix_B)
{
    vector<vector<int> > Final_matrix (Matrix_A.size(),vector<int>(Matrix_A.size(),0));
    for(int i=0;i<Matrix_A.size();i++)
        for(int j=0;j<Matrix_A.size();j++)
            for(int k=0;k<Matrix_A.size();k++)
            {
                Final_matrix[i][j]%=1000;
                Matrix_A[i][k]%=1000;
                Matrix_B[k][j]%=1000;
                Final_matrix[i][j]+=Matrix_A[i][k]*Matrix_B[k][j];
                Final_matrix[i][j]%=1000;
            }
    Matrix_A=Final_matrix;
}
void matrix_powering(vector<vector<int> > &Matrix,
                     vector<vector<int> > &Original,
                     int power)
{
    if(power%2==0)
    {
        matrix_powering(Matrix,Original,power/2);
        matrix_multiplication(Matrix,Matrix);
        return;
    }
    else if(power>1)
    {
        matrix_powering(Matrix,Original,power-1);
        matrix_multiplication(Matrix,Original);
        return;
    }
    else
        return;
}
void final_multiplication(vector<vector<int> > &Pattern_matrix,
                          vector<vector<int> > &Entry_matrix)
{
    vector<vector<int> > Final_matrix (Entry_matrix.size(),vector<int>(1,0));
    for(int i=0;i<Entry_matrix.size();i++)
        for(int j=0;j<Entry_matrix[0].size();j++)
            for(int k=0;k<Entry_matrix.size();k++)
            {
                Final_matrix[i][j]%=1000;
                Pattern_matrix[i][k]%=1000;
                Entry_matrix[k][j]%=1000;
                Final_matrix[i][j]+=Pattern_matrix[i][k]*Entry_matrix[k][j];
                Final_matrix[i][j]%=1000;
            }

    Entry_matrix=Final_matrix;
}
void print_result(int result)
{
    if(result%10==result)
        printf("00%d\n",result);
    else if(result%100==result)
        printf("0%d\n",result);
    else
        printf("%d\n",result);
}
int main()
{
    int OMOM;scanf("%d",&OMOM);
    while(OMOM--)
    {
        int recursion_deep, final_number;
        scanf("%d %d", &recursion_deep, &final_number);
        vector<vector<int> > Pattern_matrix (recursion_deep,vector<int>(recursion_deep,0));
        vector<vector<int> > Original (recursion_deep,vector<int>(recursion_deep,0));
        pattern_matrix_input(Pattern_matrix);
        Original=Pattern_matrix;
        //print_matrix(Pattern_matrix);
        vector<vector<int> > Entry_values (recursion_deep,vector<int>(1));
        entry_value_input(Entry_values);
        if(recursion_deep>=final_number)
        {
            print_result(Entry_values[final_number-1][0]%1000);
            continue;
        }
        //print_matrix(Entry_values);
        matrix_powering(Pattern_matrix,Original,final_number-recursion_deep);
        //print_matrix(Pattern_matrix);
        final_multiplication(Pattern_matrix,Entry_values);
        //print_matrix(Entry_values);
        print_result(Entry_values[Entry_values.size()-1][0]);
    }

}
