#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hamza Gunes - 12/02/2025 - Hash Table.


struct Cell{
	
	char *anahtar; //key
	struct Cell *next;
};


struct Table_node{
	
	int counter;
	struct Cell *header;
};


struct Hash_table{
	
	struct Table_node *tablo_basi; //table_head
	int multiplier;
	int table_size;
};


unsigned Hash(char *anahtar, int multiplier, int table_size){
	
	unsigned int value = 0;
	
	int i = 0;
	
	while(anahtar[i]){
		
		value = (anahtar[i] + value*multiplier) % table_size;
		i++;
	}
	
	return value;
	
}


void initialize_hash_table(struct Hash_table **hashtable, int multiplier, int table_size){
	
	*hashtable = (struct Hash_table*)malloc(sizeof(struct Hash_table));
	if(*hashtable == NULL) exit(1);
	
	(*hashtable)->tablo_basi = (struct Table_node*)malloc(table_size*sizeof(struct Table_node));
	if((*hashtable)->tablo_basi == NULL) exit(1);
	
	(*hashtable)->multiplier = multiplier;
	(*hashtable)->table_size = table_size;
	
	int i = 0;
	
	for(i=0; i<table_size; i++){
		
		((*hashtable)->tablo_basi + i)->counter = 0;
		((*hashtable)->tablo_basi + i)->header = NULL;
	}
}


int insert(char *anahtar, struct Cell **listebasi){ //liste basi means list head.
	
	if(*listebasi == NULL){
		
		*listebasi = (struct Cell*)malloc(sizeof(struct Cell));
		if(*listebasi == NULL) exit(1);
		
		(*listebasi)->anahtar = (char*)malloc((strlen(anahtar)+1)*sizeof(char));
		if((*listebasi)->anahtar == NULL) exit(1);
		
		strcpy((*listebasi)->anahtar,anahtar);
		
		(*listebasi)->next = NULL;
		
		return 1;
	}
	else if(strcmp((*listebasi)->anahtar,anahtar)){
		
		return insert(anahtar,&((*listebasi)->next));
	}
	else return 0;
}


void insert_hash_table(struct Hash_table *hashtable, char *anahtar){
	
	int index = Hash(anahtar, hashtable->multiplier, hashtable->table_size);
	
	if(insert(anahtar,&((hashtable->tablo_basi + index)->header))){
		
		(hashtable->tablo_basi + index)->counter++;
	}
}


int lookup(char *anahtar, struct Cell *listebasi){
	
	if(listebasi == NULL) return 0;
	else if(!strcmp(listebasi->anahtar,anahtar)) return 1;
	else return lookup(anahtar,listebasi->next);
}


int delete_from_list(char *anahtar, struct Cell **listebasi){
	
	if(*listebasi == NULL) return 0;
	
	struct Cell *onceki = NULL;
	struct Cell *simdiki = *listebasi;
	
	if(!strcmp((*listebasi)->anahtar,anahtar)){
		
		if((*listebasi)->next == NULL){
			
			free((*listebasi)->anahtar);
			free(*listebasi);
			*listebasi = NULL;
			return 1;
		}
		else if((*listebasi)->next != NULL){
			
			onceki = *listebasi;
			*listebasi = (*listebasi)->next;
			free(onceki->anahtar);
			free(onceki);
			return 1;
		}
	}
	else{
		
		while(simdiki && strcmp(simdiki->anahtar,anahtar)){
			
			onceki = simdiki;
			simdiki = simdiki->next;
		}
		
		if(simdiki == NULL) return 0;
		
		if(simdiki->next == NULL){
			
			free(simdiki->anahtar);
			free(simdiki);
			onceki->next = NULL;
			return 1;
		}
		else if(simdiki->next != NULL){
			
			onceki->next = simdiki->next;
			free(simdiki->anahtar);
			free(simdiki);
			return 1;
			
		}
	}
}

/*
int delete_from_list(char *anahtar, struct Cell **header){
    struct Cell *simdiki,*onceki;
    simdiki=*header;
    while(simdiki && strcmp(simdiki->anahtar,anahtar)){
        onceki=simdiki;
        simdiki=simdiki->next;
    }
    if(!simdiki) return 0;
    if(simdiki==*header){
        *header=(*header)->next;
    }else {
        onceki->next=simdiki->next;
    }
    free(simdiki->anahtar);
    free(simdiki);
    return 1;
}
*/

void delete_from_table(char *anahtar, struct Hash_table *htable){
	
	int index = Hash(anahtar,htable->multiplier,htable->table_size);
	
	if(delete_from_list(anahtar,&((htable->tablo_basi + index)->header))){
		
		(htable->tablo_basi + index)->counter--;
	}
}


void free_list(struct Cell **listebasi){
	
	struct Cell *onceki = *listebasi;
	
	while(*listebasi != NULL){
		
		onceki = *listebasi;
		*listebasi = (*listebasi)->next;
		free(onceki->anahtar);
		free(onceki);
	}
}


void free_hash(struct Hash_table **htable){
	
	
	if(*htable){
		
		int i=0;
		for(i=0;i<(*htable)->table_size;i++){
			
			free_list(&(((*htable)->tablo_basi + i)->header));
			free((*htable)->tablo_basi);
			free(*htable);
		}
		*htable = NULL;
	}
}


void expand_table(struct Hash_table **htable, int multiplier, int table_size){
	
	struct Hash_table *yenitablo;
	struct Cell *listebasi;
	
	if(*htable){
		
		initialize_hash_table(&yenitablo,multiplier,table_size);
		
		int i = 0;
		for(i=0;i<(*htable)->table_size;i++){
			
			listebasi = ((*htable)->tablo_basi + i)->header;
			
			while(listebasi != NULL){
				
				insert_hash_table(yenitablo, listebasi->anahtar);
				listebasi = listebasi->next;
			}
		}
		
		free_hash(htable);
		
		*htable = yenitablo;
	}
	
}





void print_list(struct Cell *liste_basi){
    if(liste_basi!=NULL){
        printf("%s ", liste_basi->anahtar);
        print_list(liste_basi->next);
    }
    
}


void print_hash_table(struct Hash_table *hash_table){
    if(hash_table){
        int index;
        printf("----- HASH TABLE -----\n");
        for(index=0; index<hash_table->table_size; index++){
            printf("%5d : (%2d) ",index,(hash_table->tablo_basi +index)->counter);
          //  printf("%5d : (%2d) ",index,hash_table->tablo_basi[index].counter);
            print_list((hash_table->tablo_basi+index)->header);
            printf("\n");
        }
    }
    else printf("Hash Tablosu Bos ...\n");    
}


void Fill_table_from_list(struct Hash_table *htable, struct Cell **listebasi){
	
	if(*listebasi == NULL || htable == NULL) return;
	
	struct Cell *iter = *listebasi;
	
	while(iter != NULL){
		
		int index = Hash(iter->anahtar,(htable)->multiplier,(htable)->table_size);
		struct Cell **a = &(((htable)->tablo_basi + index)->header);
		
		if(*a == NULL){
			
			*a = iter;
			iter = iter->next;
			(*a)->next = NULL;
			
		}
		else{
		
			while((*a)->next != NULL){
			
				(*a) = (*a)->next;
			}
		
			(*a)->next = iter;
			iter = iter->next;
			(*a)->next->next = NULL;
		
		}
		
		(htable->tablo_basi + index)->counter++;
	}
}


void Fill_list_from_table(struct Hash_table *htable, struct Cell **listebasi){
	
	if(htable == NULL) return;
	
	struct Cell *header,*a;
	
	int i = 0;
	for(i=0;i<htable->table_size;i++){
		
		header = (htable->tablo_basi + i)->header;
		
		while(header != NULL){
			
			if(*listebasi == NULL){
				
				*listebasi = header;
				a = header;
			}
			else{
				
				a->next = header;
				a = a->next;
			}
			
			header = header->next;
		}
		(htable->tablo_basi + i)->counter = 0;
		(htable->tablo_basi + i)->header = NULL;
	}
	if(a) a->next = NULL;
}

int main(){
	
	
	struct Hash_table *htable = NULL;
	initialize_hash_table(&htable,3,5);
	
	//Test Functions:
	
	insert_hash_table(htable,"adana");          //Turkish Cities.
	insert_hash_table(htable,"istanbul");
    insert_hash_table(htable,"izmir");
    insert_hash_table(htable,"tekirdag");
    insert_hash_table(htable,"adana");
    insert_hash_table(htable,"samsun");
    insert_hash_table(htable,"kocaeli");
    insert_hash_table(htable,"kayseri");
    insert_hash_table(htable,"everest");
	
	print_hash_table(htable);
	
	delete_from_list("izmir",&((htable->tablo_basi + Hash("izmir",3,5))->header));
	delete_from_table("adana",htable);
	
	print_hash_table(htable);
	
	expand_table(&htable,3,11);
	
	print_hash_table(htable);
	
	
	struct Cell *root = (struct Cell*)malloc(sizeof(struct Cell));
	root->anahtar = (char*)malloc((strlen("bursa")+1)*sizeof(char));
	strcpy(root->anahtar,"bursa");
	root->next = NULL;
	
	struct Cell *node1 = (struct Cell*)malloc(sizeof(struct Cell));
	node1->anahtar = (char*)malloc((strlen("duzce")+1)*sizeof(char));
	strcpy(node1->anahtar,"duzce");
	root->next = node1;
	
	struct Cell *node2 = (struct Cell*)malloc(sizeof(struct Cell));
	node2->anahtar = (char*)malloc((strlen("gebze")+1)*sizeof(char));
	strcpy(node2->anahtar,"gebze");
	node1->next = node2;
	node2->next = NULL;
	
	
	struct Hash_table *h2table = NULL;
	initialize_hash_table(&h2table,3,5);
	
	Fill_table_from_list(h2table,&root);
	
	print_hash_table(h2table);
	
	free(h2table);
}