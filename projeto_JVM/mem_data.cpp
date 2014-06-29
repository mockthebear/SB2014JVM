#include "mem_data.hpp"

void MemoryData::put_data(int index, u4 *value, char d_type) {
	if(data_index[index] == -1) {
		printf("Error index value %d: mem_data.put_data\n" ,(short)data_index[index]);
		exit(0);
	}
	
	data[ data_index[index] ] = value[0];
	if( (d_type == TYPE_LONG) || (d_type == TYPE_DOUBLE) )  {
		data[ data_index[index]+1 ] = value[1];
	}
}

void MemoryData::get_data(int index, u4 *value, char d_type) {
	if(data_index[index] == -1) {
		printf("Error index value %d: mem_data.get_data\n" ,(short)data_index[index]);
		exit(0);
	}
	
	value[0] = data[ data_index[index] ];
	if( (d_type == TYPE_LONG) || (d_type == TYPE_DOUBLE) )  {
		value[1] = data[ data_index[index]+1 ];
	}
}

void MemoryData::print() {
	printf("%c", type);
	u2 max= data_count;
	if(type == TYPE_CLASS){
		printf("%s\n", classref->get_cp_this_class());
		printf("    super: [%08X]", superInst);
		max = classref->fields_count;
	} else {
		printf("%c", array_type);
	}
	printf("\n");
	printf("    data/field: %d\n",data_count);
	printf("    ");
	for(u2 i=0;i<max; i++) {
		if(data_index[i] != -1) {
			char d_type;
			
			if(type == TYPE_CLASS) {
				d_type = *( classref->get_field_type(i) );
			} else {
				d_type = array_type;
			}
			printf("[%d] ",data_index[i]);
			printf("(%c) ",d_type);
			printf("%08X  ", data[ data_index[i] ]);
			if( (d_type == TYPE_LONG) || (d_type == TYPE_DOUBLE) ) {
				printf("[%d] ",data_index[i]+1);
				printf("(%c) ",d_type);
				printf("%08X  ", data[ data_index[i]+1 ]);
			}
		}
	}
	printf("\n");
}
