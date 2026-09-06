#ifndef VECTOR_STOREIO
#define VECTOR_STOREIO

#include<iostream>
#include<vector>
#include<fstream>
#include"Vector_Record.h"

template<typename T>
class vector_storeIO{
    public:
        static std::vector<VectorRecord<T>> read_vecs(const std::string& file_path){
            std::vector<VectorRecord<T>> all_records;
            std::ifstream file(file_path,std::ios::binary);
            if(!file.open()){
                throw std::runtime_error("fuck");
            }
            int dim,id=0;
            while(file.read(reinterpret_cast<char*>(&dim),sizeof(dim))){
                if(dim>0){
                    VectorRecord<T> record;
                    record.vector.resize(dim);
                    record.id=id;
                    id++;
                    for(int i=0;i<dim;i++){
                        if(!file.read(reinterpret_cast<char*>(&record.vector[i]),sizeof(T))){
                            throw std::runtime_error("Noo");
                        }
                    }
                    all_records.push_back(record);
                }
            }
            return all_records;
        }
};


#endif