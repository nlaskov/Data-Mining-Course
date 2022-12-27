package Algorithms;
public class Rotate_Matrix {

    static void display(int matrix[][])
    {
        for(int i=0;i<matrix.length;i++){
            for(int j=0;j<matrix.length-1;j++){
                System.out.print(matrix[i][j] + "_");
            }
            System.out.println(matrix[i][matrix.length-1]);
        }
    }

    public static void rotate(int count, int[][] matrix){
        final int size = matrix.length;
        count = count%4;
        for(int i=0;i<size /2 ;i++){
            for(int j= i; j<size -1-i;j++){
                for(int h=0;h<count;h++){
                    int temp = matrix[i][j];
                    matrix[i][j] = matrix[size - 1 - j][i];
                    matrix[size - 1 - j][i] = matrix[size - 1 - i][size - 1 - j];
                    matrix[size - 1 - i][size - 1 - j] = matrix[j][size - 1 - i];
                    matrix[j][size - 1 - i] = temp;
                }  
            }
        }
    }

    public static void main(String[] args) {
        
        int matrix[][] = {  {1,2,3},
                            {4,5,6},
                            {7,8,9}
                        };

        rotate(2, matrix);

        display(matrix);
    }


}
