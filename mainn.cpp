#include <iostream>
#include <vector>
#include <cstdlib>

std::vector<std::vector<int>> create_matrix(std::size_t n){
    std::vector<std::vector<int>> matrix(n,std::vector<int>(n,0));

    for(size_t i=0;i<n;i++){
        for(size_t j=i+1;j<n;j++){
            int value=rand()%2;
            matrix[i][j]=value;
            matrix[j][i]=value;
        }
    }
    return matrix;
}

void print_matrix(std::vector<std::vector<int>>& matrix){
    for(size_t i=0;i<matrix.size();i++){
        for(size_t j=0;j<matrix[i].size();j++){
            std::cout<<matrix[i][j]<<" "; 
        }
        std::cout<<"\n";
    }
}

size_t count_reber(const std::vector<std::vector<int>>& matrix){
    int edges=0;
    for(size_t i=0;i<matrix.size();i++){
        for(size_t j=i+1;j<matrix.size();j++){
            edges+=matrix[i][j];
        }
    }
    return edges;
}

void print_vershin(const std::vector<size_t>& degrees,size_t value){
    bool found=false;
    for(size_t i=0;i<degrees.size();i++){
        if(degrees[i]==value){
            std::cout<<i+1<<' ';
            found=true;
        }
    }
    if(!found)std::cout<<"нет";
    std::cout<<'\n';
}

void print_info_vershin(const std::vector<std::vector<int>>& matrix,size_t edges){
    size_t n=matrix.size();
    std::vector<size_t> degrees(n,0);

    for(size_t i=0;i<n;i++){
        for(size_t j=0;j<matrix[i].size();j++){
            degrees[i]+=matrix[i][j];
        }
    }

    for(size_t i=0;i<n;i++){
        std::cout<<"Вершина "<<i+1<<": "<<degrees[i]<<'\n';
    }
    std::cout<<"\n";

    std::cout<<"Изолированные вершины: ";
    print_vershin(degrees,0);
    
    std::cout<<"Концевые вершины: ";
    print_vershin(degrees,1);

    std::cout<<"Доминирующие вершины: ";
    print_vershin(degrees,n-1);
}

std::vector<std::vector<int>> create_matrix1(const std::vector<std::vector<int>>& matrix){
    size_t n=matrix.size();
    size_t m=count_reber(matrix);
    std::vector<std::vector<int>> matrix1(n,std::vector<int>(m,0));

    size_t k=0;
    for(size_t i=0;i<n;i++){
        for(size_t j=i+1;j<n;j++){
            if(matrix[i][j]==1){
                matrix1[i][k]=1;
                matrix1[j][k]=1;
                k++;
            }
        }
    }
    return matrix1;
}

int main(){
    int n;
    std::cout<<"Введите размер графа: ";
    if(!(std::cin>>n)||n<=0){
        std::cout<<"НЕ ВЕРНЫЙ ВВОД.\nРАЗМЕР ДОЛЖЕН БЫТЬ ЧИСЛОМ БОЛЬШЕ НУЛЯ\n";
        return 1;
    }
    std::cout<<"\n";

    std::vector<std::vector<int>> matrix=create_matrix(n);

    std::cout<<"МАТРИЦА СМЕЖНОСТИ:\n";
    print_matrix(matrix);

    std::cout<<"РАЗМЕР ГРАФА: "<<count_reber(matrix)<<"\n";

    std::size_t edges=count_reber(matrix);
    print_info_vershin(matrix,edges);

    std::vector<std::vector<int>> matrix2=create_matrix1(matrix);
    std::size_t edges2=matrix2[0].size();

    std::cout<<"\nМАТРИЦА ИНЦИДЕНТНОСТИ:\n";
    if(edges2==0){
        std::cout<<"Ребер нет: матрица содержит "<<n<<" строк и 0 столбцов\n";
    }
    else{
        print_matrix(matrix2);
    }
    print_info_vershin(matrix2,edges2);

    return 0;
}