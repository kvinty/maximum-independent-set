%module mis

%{
#include "mis.hxx"
%}

%include "std_array.i"
%template(array_int_2) std::array<int, 2>;

%include "std_vector.i"
%template(vector_int) std::vector<int>;
%template(vector_array_int_2) std::vector<std::array<int, 2>>;

%include "mis.hxx"
