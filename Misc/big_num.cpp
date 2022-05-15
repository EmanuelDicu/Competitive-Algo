	
class Huge : protected vector<int> {
protected:
    bool sign;
    static const int nbase = 9;
    static const int size = 5;
    static const int base = 1e9;
public:
    
    // CONSTRUCTORS
    
    Huge() {
        this -> sign = true;
        this -> resize( size );
    }
    
    template <typename type>
    Huge( type other ) {
        this -> sign = other >= 0;
        this -> resize( size );
        
        for( ; other != 0; other /= base )
            (*this)[++ (*this)[0]] = other % base;
    }
    
    Huge( const char *other ) {
        this -> sign = *other != '-';
        this -> resize( size );
        *this = other;
    }
    
    // RELATIONAL OPERATORS
    
    int comp( const Huge &other ) const {
        if( this -> sign != other.sign )
            return this -> sign < other.sign ? -1 : 1;
        
        if( this -> size != other.size ) {
            if( this -> sign == false )
                return this -> size > other.size ? -1 : 1;
            else
                return this -> size < other.size ? -1 : 1;
        }
        
        for( int i = (*this)[0]; i >= 1; i -- ) {
            if( (*this)[i] != other[i] ) {
                if( this -> sign == false )
                    return (*this)[i] > other[i] ? -1 : 1;
                else
                    return (*this)[i] < other[i] ? -1 : 1;
            }
        }
        
        return 0;
    }
    
    bool operator < ( const Huge &other ) const {
        return this -> comp( other ) < 0;
    }
    
    bool operator <= ( const Huge &other ) const {
        return this -> comp( other ) <= 0;
    }
    
    bool operator > ( const Huge &other ) const {
        return this -> comp( other ) > 0;
    }
    
    bool operator >= ( const Huge &other ) const {
        return this -> comp( other ) >= 0;
    }
    
    bool operator == ( const Huge &other ) const {
        return this -> comp( other ) == 0;
    }
    
    bool operator != ( const Huge &other ) const {
        return this -> comp( other ) != 0;
    }
    
    template <typename type>
    bool operator < ( const type _other ) const {
        Huge other( _other );
        return this -> comp( other ) < 0;
    }
    
    template <typename type>
    bool operator <= ( const type _other ) const {
        Huge other( _other );
        return this -> comp( other ) <= 0;
    }
    
    template <typename type>
    bool operator > ( const type _other ) const {
        Huge other( _other );
        return this -> comp( other ) > 0;
    }
    
    template <typename type>
    bool operator >= ( const type _other ) const {
        Huge other( _other );
        return this -> comp( other ) >= 0;
    }
    
    template <typename type>
    bool operator == ( const type _other ) const {
        Huge other( _other );
        return this -> comp( other ) == 0;
    }
    
    template <typename type>
    bool operator != ( const type _other ) const {
        Huge other( _other );
        return this -> comp( other ) != 0;
    }

    bool operator < ( const char *_other ) const {
        Huge other( _other );
        return this -> comp( other ) < 0;
    }
    
    bool operator <= ( const char *_other ) const {
        Huge other( _other );
        return this -> comp( other ) <= 0;
    }
    
    bool operator > ( const char *_other ) const {
        Huge other( _other );
        return this -> comp( other ) > 0;
    }
    
    bool operator >= ( const char *_other ) const {
        Huge other( _other );
        return this -> comp( other ) >= 0;
    }
    
    bool operator == ( const char *_other ) const {
        Huge other( _other );
        return this -> comp( other ) == 0;
    }
    
    bool operator != ( const char *_other ) const {
        Huge other( _other );
        return this -> comp( other ) != 0;
    }

    // ARITHMETIC OPERATORS
    
    Huge operator + ( Huge &other ) {
        Huge sum;
        
        int i = 0, t = 0;
        if( this -> sign == other.sign ) {
            sum.sign = this -> sign;
            
            for( ; i <= (*this)[0] && i <= other[0] && t; i ++, t /= this -> base )
                sum[i] = ( t += (*this)[i] + other[i] ) / base;
            sum[0] = i - 1;
        }
        else {
            bool sign1 = this -> sign; this -> sign = true;
            bool sign2 = other.sign; other.sign = true;
            
            if( *this >= other ) {
                sum.sign = this -> sign;
                
                for( ; i <= (*this)[0]; i ++ ) {
                    sum[i] = ( (*this)[i] - other[i] ) + t;
                    sum[i] += ( t = sum[i] < 0 ) * base;
                }
            }
            else {
                sum.sign = other.sign;
                
                for( ; i <= other[0]; i ++ ) {
                    sum[i] = ( other[i] - (*this)[i] ) + t;
                    sum[i] += ( t = sum[i] < 0 ) * base;
                }
            }
            
            sum[0] = i - 1;
            while( sum[0] > 0 && sum[sum[0]] == 0 )
                sum[0] --;
            
            this -> sign = sign1;
            other.sign = sign2;
        }
        
        return sum;
    }
    
    Huge operator - ( Huge &other ) {
        Huge dif;
        
        int i = 0, t = 0;
        if( this -> sign != other.sign ) {
            dif.sign = this -> sign;
            
            for( ; i <= (*this)[0] && i <= other[0] && t; i ++, t /= this -> base )
                dif[i] = ( t += (*this)[i] + other[i] ) / base;
            dif[0] = i - 1;
        }
        else {
            bool sign1 = this -> sign; this -> sign = true;
            bool sign2 = other.sign; other.sign = true;
            
            if( *this >= other ) {
                dif.sign = this -> sign;
                
                for( ; i <= (*this)[0]; i ++ ) {
                    dif[i] = ( (*this)[i] - other[i] ) + t;
                    dif[i] += ( t = dif[i] < 0 ) * base;
                }
            }
            else {
                dif.sign = !other.sign;
                
                for( ; i <= other[0]; i ++ ) {
                    dif[i] = ( other[i] - (*this)[i] ) + t;
                    dif[i] += ( t = dif[i] < 0 ) * base;
                }
            }
            
            dif[0] = i - 1;
            while( dif[0] > 0 && dif[dif[0]] == 0 )
                dif[0] --;
            
            this -> sign = sign1;
            other.sign = sign2;
        }
    
        return dif;
    }
    
    Huge operator * ( Huge &other ) {
        Huge prod;
        prod.sign = !(this -> sign ^ other.sign);
        
        int i, j; long long t;
        for( i = 1; i <= (*this)[0]; i ++ ) {
            for( j = 1, t = 0; j <= other[0] || t; j ++, t /= base )
                prod[i + j - 1] = ( t += prod[i + j - 1] + 1LL * (*this)[i] * other[j] ) % base;
            prod[0] = max( prod[0], i + j - 2 );
        }
        
        return prod;
    }
  
    Huge operator / ( Huge &other ) {
        Huge div;
        
        // nope
        
        return div;
    }
    
    Huge operator % ( Huge &other ) {
        Huge mod;
        
        // nope
        
        return mod;
    }
  
    template <typename type>
    Huge operator + ( type _other ) {
        Huge other( _other );
        return (*this) + other;
    }
    
    template <typename type>
    Huge operator - ( type _other ) {
        Huge other( _other );
        return (*this) - other;
    }
    
    template <typename type>
    Huge operator * ( type _other ) {
        Huge other( _other );
        return (*this) * other;
    }
    
    template <typename type>
    Huge operator / ( type _other ) {
        Huge div;
        
        int i; long long t = 0;
        for( i = (*this)[0]; i >= 1; i --, t %= _other )
            div[i] = ( t = t * base + (*this)[i] ) / _other;
        
        div[0] = (*this)[0];
        while( div[0] > 0 && div[div[0]] == 0 )
            div[0] --;
        
        return div;
    }
    
    template <typename type>
    type operator % ( type _other ) {
        
        int i; long long t = 0;
        for( i = (*this)[0]; i >= 1; i -- )
            t = ( t * base + (*this)[i] ) % _other;
        
        return t;
    }
    
    Huge operator + ( char *_other ) {
        Huge other( _other );
        return (*this) + other;
    }
    
    Huge operator - ( char *_other ) {
        Huge other( _other );
        return (*this) - other;
    }
    
    Huge operator * ( char *_other ) {
        Huge other( _other );
        return (*this) * other;
    }
    
    Huge operator / ( char *_other ) {
        Huge other( _other );
        return (*this) / other;
    }
    
    Huge operator % ( char *_other ) {
        Huge other( _other );
        return (*this) % other;
    }
    
    // ASSIGNMENT OPERATORS
    
    Huge &operator += ( Huge other ) {
        *this = *this + other;
        return *this;
    }
 
    Huge &operator -= ( Huge other ) {
        *this = *this - other;
        return *this;
    }
    
    Huge &operator *= ( Huge other ) {
        *this = *this * other;
        return *this;
    }
    /*
    Huge &operator /= ( Huge other ) {
        *this = *this / other;
        return *this;
    }
    
    Huge &operator %= ( Huge other ) {
        *this = *this % other;
        return *this;
    }
    */
    template <typename type>
    Huge &operator = ( type _other ) {
        Huge other( _other );
        *this = other;
        return *this;
    }
    
    template <typename type>
    Huge operator += ( type _other ) {
        Huge other( _other );
        *this = (*this) + other;
        return *this;
    }
    
    template <typename type>
    Huge operator -= ( type _other ) {
        Huge other( _other );
        *this = (*this) - other;
        return *this;
    }
    
    template <typename type>
    Huge operator *= ( type _other ) {
        Huge other( _other );
        *this = (*this) * other;
        return *this;
    }
    
    template <typename type>
    Huge operator /= ( type _other ) {
        //Huge other( _other );
        *this = (*this) + _other;
        return *this;
    }
    
    template <typename type>
    Huge operator %= ( type _other ) {
        //Huge other( _other );
        *this = (*this) % _other;
        return *this;
    }
    
    template <typename type>
    Huge &operator = ( char *_other ) {
        Huge other( _other );
        *this = other;
        return *this;
    }
    
    Huge operator += ( char *_other ) {
        Huge other( _other );
        *this = (*this) + other;
        return *this;
    }
    
    Huge operator -= ( char *_other ) {
        Huge other( _other );
        *this = (*this) - other;
        return *this;
    }
    
    Huge operator *= ( char *_other ) {
        Huge other( _other );
        *this = (*this) * other;
        return *this;
    }
    
    Huge operator /= ( char *_other ) {
        Huge other( _other );
        *this = (*this) + other;
        return *this;
    }
    
    Huge operator %= ( char *_other ) {
        Huge other( _other );
        *this = (*this) % other;
        return *this;
    }
    
    // STREAM OPERATORS
    
    friend istream &operator >> ( istream &input, Huge &other ) {
        string str;
        input >> str;
        
        other[0] = 0;
        for( int i = (int) str.size() - 1; i >= ( str[0] == '-' ); i -= nbase ) {
            other[++ other[0]] = 0;
            for( int j = max( 0, i - nbase + 1 ); j <= i; j ++ )
                other[other[0]] = other[other[0]] * 10 + ( str[j] - '0' );
        }
        
        return input;
    }
    
    friend ostream &operator << ( ostream &output, const Huge &other ) {
        if( other[0] == 0 )
            output << 0;
        else {
            if( other.sign == false )
                output << '-';
            output << other[other[0]];
            for( int i = other[0] - 1; i >= 1; i -- ) {
                for( int p = base / 10; p > other[i] && p > 1; p /= 10 )
                    output << 0;
                output << other[i];
            }
        }
        
        return output;
    }
};