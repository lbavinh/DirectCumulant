#include <stdio.h>
#include <vector>
#include <array>
#include <algorithm>
#include <math.h>
#include <set>
#include <string>
#include <cstring>
#include <map>
#include <stdlib.h>

using namespace std;

const int MAX_ORDER = 16;


/*
    next
        - given the partitioning scheme represented by s and m, generate the next
    Returns: 1, if a valid partitioning was found 0, otherwise
*/
int next(array<int, MAX_ORDER> &s, array<int, MAX_ORDER> &m, int n) {
    /* Update s: 1 1 1 1 -> 2 1 1 1 -> 1 2 1 1 -> 2 2 1 1 -> 3 2 1 1 -> 1 1 2 1 ... */
    int i = 0;
    ++s[i];
    while ((i < n - 1) && (s[i] > m[i] + 1)) {
        s[i] = 1;
        ++i;
        ++s[i];
    }

    /* If i has reached the n-1 element, then the last unique partitiong has been found*/
    if (i == n - 1)
        return 0;

    /* Because all the first i elements are now 1, s[i] (i + 1 element) is the largest. 
    So we update max by copying it to all the first i positions in m.*/
    int max = s[i];
    for (i = i - 1; i >= 0; --i)
        m[i] = max;

    return 1;
}

void print_as_Qvs( array<int, MAX_ORDER> s, int n, int np ){

    for ( int i = 1; i < np+1; i++ ){
        printf( "<" );
        char* space = "";
        for ( int j =0; j < n; j++ ){
            if ( s[j] == i ){
                printf( "%sQ_%d", space, j+1 );
                space = " ";
            }
        }
        printf( ">" );
    }
    
}

int max_in_map( map<int, int> &m ){

    int v = 0;
    for ( auto kv : m ){
        if ( kv.second > v ){
            v = kv.second;
        }
    }
    return v;
}

int factorial( int n ){
    if ( n <= 1 ) return 1;
    return n * factorial( n - 1 );
}
int coeff( int n ){
    return pow( -1, n-1 ) * factorial( n - 1 );
}


// USAGE
// part.app <h> 
// h - default = 2
// 
int main(int argc, char *argv[]) {
    /* s[i] is the number of the set in which the i element should go */
    /* m[i] is the largest of the first i elements in s*/

    array<int, MAX_ORDER> s;
    array<int, MAX_ORDER> m;
    vector< array<int, MAX_ORDER> > v;

    int n = 3;
    if ( argc > 1 )
        n = atoi( argv[1] );
    int i;
    /* The first way to partition a set is to put all the elements in the same
       subset. */
    for (i = 0; i < n; ++i) {
        s[i] = 1;
        m[i] = 1;
    }


    v.push_back( s );

    /* Print the other partitioning schemes. */
    while (next(s, m, n)){
        v.push_back( s );
    }



    printf( "h = %d --> # of terms = %lu \n", n, v.size() );
    
    //for ( int k = 1; k < n+1; k++){ 
        //extra loop (k) used to print them in order like in paper
        //for ( int a = n+1; a > 0; --a ){
            //extra loop (a) used to print them in order like in paper


            for ( int j = 0; j < v.size(); j++ ){
                
                set<int> parts;
                map<int, int> largest_part;
                string msg = "";
                for ( int i = 0; i < n; i++ ){
                    char buf[50];
                    sprintf( buf, "[%d]", v[j][i] );
                    msg = msg + string(buf);
                    parts.insert( v[j][i] );
                    largest_part[ v[j][i] ]++;
                }

                //if ( parts.size() != k || max_in_map( largest_part ) != a ) continue;
                printf( "%s", msg.c_str() );;
                printf( " => %+d * ", coeff( parts.size() ) );
                print_as_Qvs( v[j], n, parts.size() );
                printf( "\n" );
            //}
        //}
    }

        

    return 0;
}
