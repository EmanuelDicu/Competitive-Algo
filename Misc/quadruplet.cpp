	
template <typename type1, typename type2, typename type3, typename type4>
class Quadruplet {
public:
    type1 first; type2 second; type3 third; type4 fourth;
    
    // CONSTRUCTORS
    
    Quadruplet() {
        this -> first = 0;
        this -> second = 0;
        this -> third = 0;
        this -> fourth = 0;
    }
    
    Quadruplet( type1 first, type2 second, type3 third, type4 fourth ) {
        this -> first = first;
        this -> second = second;
        this -> third = third;
        this -> fourth = fourth;
    }
    
    // RELATIONAL OPERATORS
    
    int comp( const Quadruplet<type1, type2, type3, type4> &other ) const {
        if( this -> first != other.first )
            return this -> first < other.first ? -1 : 1;
        if( this -> second != other.second )
            return this -> second < other.second ? -1 : 1;
        if( this -> third != other.third )
            return this -> third < other.third ? -1 : 1;
        if( this -> fourth != other.first )
            return this -> fourth < other.fourth ? -1 : 1;
        return 0;
    }
    
    bool operator < ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        return this -> comp( other ) < 0;
    }
    
    bool operator <= ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        return this -> comp( other ) <= 0;
    }
    
    bool operator > ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        return this -> comp( other ) > 0;
    }
    
    bool operator >= ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        return this -> comp( other ) >= 0;
    }
    
    bool operator == ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        return this -> comp( other ) == 0;
    }
    
    bool operator != ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        return this -> comp( other ) != 0;
    }
    
    // ARITHMETIC OPERATORS
    
    Quadruplet operator + ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        return Quadruplet( this -> first + other.first,
                           this -> second + other.second,
                           this -> third + other.third,
                           this -> fourth + other.fourth );
    }
    
    Quadruplet operator - ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        return Quadruplet( this -> first - other.first,
                           this -> second - other.second,
                           this -> third - other.third,
                           this -> fourth - other.fourth );
    }
    
    Quadruplet operator * ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        return Quadruplet( this -> first * other.first,
                           this -> second * other.second,
                           this -> third * other.third,
                           this -> fourth * other.fourth );
    }
    
    Quadruplet operator / ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        return Quadruplet( this -> first / other.first,
                           this -> second / other.second,
                           this -> third / other.third,
                           this -> fourth / other.fourth );
    }
    
    Quadruplet operator % ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        return Quadruplet( this -> first % other.first,
                           this -> second % other.second,
                           this -> third % other.third,
                           this -> fourth % other.fourth );
    }
    
    // ASSIGNMENT OPERATORS
    
    Quadruplet &operator += ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        *this = *this + other;
        return *this;
    }
    
    Quadruplet &operator -= ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        *this = *this - other;
        return *this;
    }
    
    Quadruplet &operator *= ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        *this = *this * other;
        return *this;
    }
    
    Quadruplet &operator /= ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        *this = *this / other;
        return *this;
    }
    
    Quadruplet &operator %= ( const Quadruplet<type1, type2, type3, type4> &other ) const {
        *this = *this % other;
        return *this;
    }
    
    // STREAM OPERATORS
    
    friend istream &operator >> ( istream &input, Quadruplet<type1, type2, type3, type4> &other ) {
        input >> other.first >> other.second >> other.third >> other.fourth;
        return input;
    }
    
    friend ostream &operator << ( ostream &output, const Quadruplet<type1, type2, type3, type4> &other ) {
        output << other.first << " " << other.second << " " << other.third << " " << other.fourth;
        return output;
    }
};