	
template <typename type1, typename type2, typename type3>
class Triplet {
public:
    type1 first; type2 second; type3 third;
    
    // CONSTRUCTORS
    
    Triplet() {
        this -> first = 0;
        this -> second = 0;
        this -> third = 0;
    }
    
    Triplet( type1 first, type2 second, type3 third ) {
        this -> first = first;
        this -> second = second;
        this -> third = third;
    }
    
    // RELATIONAL OPERATORS
    
    int comp( const Triplet<type1, type2, type3> &other ) const {
        if( this -> first != other.first )
            return this -> first < other.first ? -1 : 1;
        if( this -> second != other.second )
            return this -> second < other.second ? -1 : 1;
        if( this -> third != other.third )
            return this -> third < other.third ? -1 : 1;
        return 0;
    }
   
    bool operator < ( const Triplet<type1, type2, type3> &other ) const {
        return this -> comp( other ) < 0;
    }
    
    bool operator <= ( const Triplet<type1, type2, type3> &other ) const {
        return this -> comp( other ) <= 0;
    }
    
    bool operator > ( const Triplet<type1, type2, type3> &other ) const {
        return this -> comp( other ) > 0;
    }
    
    bool operator >= ( const Triplet<type1, type2, type3> &other ) const {
        return this -> comp( other ) >= 0;
    }
    
    bool operator == ( const Triplet<type1, type2, type3> &other ) const {
        return this -> comp( other ) == 0;
    }
    
    bool operator != ( const Triplet<type1, type2, type3> &other ) const {
        return this -> comp( other ) != 0;
    }
    
    // ARITHMETIC OPERATORS
    
    Triplet operator + ( const Triplet<type1, type2, type3> &other ) const {
        return Triplet( this -> first + other.first,
                        this -> second + other.second,
                        this -> third + other.third );
    }
    
    Triplet operator - ( const Triplet<type1, type2, type3> &other ) const {
        return Triplet( this -> first - other.first,
                        this -> second - other.second,
                        this -> third - other.third );
    }
    
    Triplet operator * ( const Triplet<type1, type2, type3> &other ) const {
        return Triplet( this -> first * other.first,
                        this -> second * other.second,
                        this -> third * other.third );
    }
    
    Triplet operator / ( const Triplet<type1, type2, type3> &other ) const {
        return Triplet( this -> first / other.first,
                        this -> second / other.second,
                        this -> third / other.third );
    }
    
    Triplet operator % ( const Triplet<type1, type2, type3> &other ) const {
        return Triplet( this -> first % other.first,
                        this -> second % other.second,
                        this -> third % other.third );
    }
    
    // ASSIGNMENT OPERATORS
    
    Triplet &operator += ( const Triplet<type1, type2, type3> &other ) const {
        *this = *this + other;
        return *this;
    }
    
    Triplet &operator -= ( const Triplet<type1, type2, type3> &other ) const {
        *this = *this - other;
        return *this;
    }
    
    Triplet &operator *= ( const Triplet<type1, type2, type3> &other ) const {
        *this = *this * other;
        return *this;
    }
    
    Triplet &operator /= ( const Triplet<type1, type2, type3> &other ) const {
        *this = *this / other;
        return *this;
    }
    
    Triplet &operator %= ( const Triplet<type1, type2, type3> &other ) const {
        *this = *this % other;
        return *this;
    }
    
    // STREAM OPERATORS
    
    friend istream &operator >> ( istream &input, Triplet<type1, type2, type3> &other ) {
        input >> other.first >> other.second >> other.third;
        return input;
    }
    
    friend ostream &operator << ( ostream &output, const Triplet<type1, type2, type3> &other ) {
        output << other.first << " " << other.second << " " << other.third;
        return output;
    }
};