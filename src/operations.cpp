#include "matrix.hpp"

#include <iostream>

using namespace std;

Matrix Matrix :: operator = ( const Matrix & B ){
    this -> Copy( B );

    return * this;
}

Matrix Matrix :: operator * ( const Matrix & B ){
    Matrix P;

    if( this -> GetN( ) != B.GetM( ) or this -> GetN( ) <= 0 or this -> GetM( ) <= 0 or B.GetN( ) <= 0 ){
        P.Zeros( 1, 1 );
        return P;
    }

    P.SetDimentions( this -> GetM( ), B.GetN( ) );

    for( int column = 0; column < P.GetN( ); column ++ ){
        for( int row = 0; row < P.GetM( ); row ++ ){
            double sum = 0;
            for( int i = 0; i < this -> GetN( ); i ++ ){
                sum += this -> GetIndex( row, i ) * B.GetIndex( i, column );
            }
            P.SetIndex( row, column, sum );
        }
    }

    return P;
}

Matrix Matrix :: operator + ( const Matrix & B ){
    Matrix P;

    if( this -> GetN( ) != B.GetN( ) or this -> GetN( ) <= 0 or this -> GetM( ) != B.GetM( ) or this -> GetM( ) <= 0 ){
        P.Zeros( 1, 1 );
        return P;
    }

    P.SetDimentions( this -> GetM( ), this -> GetN( ) );

    for( int column = 0; column < P.GetN( ); column ++ ){
        for( int row = 0; row < P.GetM( ); row ++ ){
            P.SetIndex( row, column, this -> GetIndex( row, column ) + B.GetIndex( row, column ) );
        }
    }
    
    return P;

}

long double Matrix :: Determinant( const Matrix & B ) const {
    if( B.GetN( ) != B.GetM( ) ){
        return 1;
    }

    if( B.GetN( ) == 0 or B.GetM( ) == 0 ){
        return 1;
    }

    if( B.GetN( ) == 1 ){
        return B.GetIndex( 0, 0 );
    }

    Matrix copy;
    
    copy.Copy( B );

    double determinant = 1;

    int exchanges = copy.TriangularSuperior( );

    for( int diag = 0; diag < copy.GetN( ); diag ++ ){
        determinant *= copy.GetIndex( diag, diag ); 
    }
    
    if( exchanges % 2 == 1 ){
        return - 1 * determinant; 
    }

    return determinant;
}

