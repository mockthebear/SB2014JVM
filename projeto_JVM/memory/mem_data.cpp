#include "mem_data.hpp"

void MemoryData::put_data(int index, u4 *in_data, u1 in_type) {
	u1 d_type;
	
	if(type == TYPE_CLASS)
		d_type = *( classref->get_field_type(index) );
	else
		d_type = array_type; 
	
	if(d_type != in_type) {
		printf("Error data type %c != %c: mem_data.put_data\n",in_type,d_type);
		exit(0);
	}
	if(data_index[index] == -1) {
		printf("Error index value %d: mem_data.put_data\n" ,(short)data_index[index]);
		exit(0);
	}
	
	data[ data_index[index] ] = in_data[0];
	if( (d_type == TYPE_LONG) || (d_type == TYPE_DOUBLE) )
		data[ data_index[index]+1 ] = in_data[1];
}

void MemoryData::get_data(int index, u4 *out_data, u1 out_type) {
	u1 d_type;
		
	if(type == TYPE_CLASS)
		d_type = *( classref->get_field_type(index) );
	else
		d_type = array_type; 
	
	if(d_type != out_type) {
		printf("Error data type %c != %c: mem_data.get_data\n",out_type,d_type);
		exit(0);
	}
	if(data_index[index] == -1) {
		printf("Error index value %d: mem_data.get_data\n" ,(short)data_index[index]);
		exit(0);
	}
	
	out_data[0] = data[ data_index[index] ];
	if( (d_type == TYPE_LONG) || (d_type == TYPE_DOUBLE) )
		out_data[1] = data[ data_index[index]+1 ];
	
}

void MemoryData::print() {
	printf("MemoryData\n");
	printf("type: %c\n", type);
	u2 max= data_count;
	if(type == TYPE_CLASS){
		printf("class: %s\n", classref->get_cp_this_class());
		max = classref->fields_count;
	}
	printf("data: %d\n", data_count);
	for(u2 i=0;i<max; i++) {
		if(data_index[i] != -1) {
			printf("[%d]->[%d] ",i,data_index[i]);
			u1 d_type;
			if(type == TYPE_CLASS) {
				d_type = *( classref->get_field_type(i) );
				printf("%c| ",d_type);
				printf("%s\t", classref->get_field_name(i));
			} else {
				d_type = array_type;
				printf("%c| ",d_type);
			}
			printf("%08X", data[ data_index[i] ]);
			if( (d_type == TYPE_LONG) || (d_type == TYPE_DOUBLE) ) {
				printf("%08X", data[ data_index[i]+1 ]);
			}
			printf("\n");
		}
	}
		
}

void MemoryData::print_min() {
	printf("%c", type);
	u2 max= data_count;
	if(type == TYPE_CLASS){
		printf("%s", classref->get_cp_this_class());
	} else {
		printf("%c", array_type);
	}	
}
