#include<stdio.h>
#define boolean int
#define false 0
#define true 1

struct bTreeNode
{
	struct bTreeDataNode 
	{
		int* val;
		int size;
		struct bTreeDataNode *parent,**child;
	}*dataRoot;
	int nodeSize;
};

//bTreeNodeSize repersents the no of values inside a b-plus node
struct bTreeNode* createBTreeNode(int bTreeNodeSize)
{
	int i=0;
	struct bTreeNode *temp = (struct bTreeNode*)malloc(sizeof(struct bTreeNode));
	temp->nodeSize = bTreeNodeSize;
	temp->dataRoot = (struct bTreeDataNode*)malloc(sizeof(struct bTreeDataNode));
	temp->dataRoot->val = (int*)malloc(sizeof(int)*bTreeNodeSize);
	temp->dataRoot->size = 0;
	temp->dataRoot->parent = NULL;
	temp->dataRoot->child = (struct bTreeDataNode**)malloc(sizeof(struct bTreeDataNode*)*(bTreeNodeSize+1));
	for(;i<=bTreeNodeSize;++i)
	{
		*(temp->dataRoot->child + i) = NULL;
	}
	/*for(i=0;i<=bTreeNodeSize;++i)
	{
		printf("%p\n", *(temp->root->child + i) );
	}*/
	return temp;
}

struct bTreeDataNode* searchData(struct bTreeDataNode *dataRoot,int secVal)
{
	int i;
	if(dataRoot == NULL)
	{
		return NULL;
	}
	for(i = 0; i < dataRoot->size; ++i)
	{
		if(*(dataRoot->val + i) == secVal)
		{
			return dataRoot;
		}
		else if(*(dataRoot->val +i) > secVal)
		{
			return searchData(*(dataRoot->child + i),secVal);
		}
	}
	return searchData(*(dataRoot->child + i),secVal);
}

struct bTreeDataNode* searchInBTreeTree(struct bTreeNode *root,int secVal)
{
	return searchData(root->dataRoot,secVal);
}

struct bTreeDataNode* bTreeInserterroot(struct bTreeDataNode *dataRoot,int nodeSize,int priVal)
{
    struct bTreeDataNode *childNode = NULL;
    int i = 0, totalSize = dataRoot->size;
    for( ; i < totalSize ; ++i )
    {
    	if( *(dataRoot->val + i) > priVal)
    	{
    		break;
    	}
    	else if( *(dataRoot->val + i) == priVal)
    	{
    		return NULL;
    	}
    }

	if( *(dataRoot->child + i) != NULL )
	{
		childNode = bTreeInserterroot(*(dataRoot->child + i),nodeSize,priVal);
		if(childNode != NULL)
		{
			priVal = *(childNode->val);
			for( i = 0 ; i < totalSize ; ++i )
		    {
		    	if( *(dataRoot->val + i) > priVal)
		    	{
		    		break;
		    	}
		    }
		}
		else
		{
			return NULL;
		}
	}
	
	if(totalSize < nodeSize)
	{
		int j=totalSize;
		for( ; j > i ; --j)
		{
			*(dataRoot->val + j) = *(dataRoot->val + j - 1);
		}
		*(dataRoot->val + j) = priVal;
		++(dataRoot->size);
		
		if(childNode != NULL)
		{
			*(dataRoot->child + i) = *(childNode->child);
			*(dataRoot->child + i + 1) = *(childNode->child + 1);
			(*(childNode->child))->parent = (*(childNode->child + 1))->parent = dataRoot;
		}
		
		return NULL;
	}
	else
	{
		//break up the node
		int j,k,childCounter = 0;
		struct bTreeDataNode *tempData1,*tempData2;

		//creating two new nodes
		tempData1 = (struct bTreeDataNode*)malloc(sizeof(struct bTreeDataNode));
		tempData1->val = (int*)malloc(sizeof(int)*nodeSize);
		tempData1->size = 0;
		tempData1->parent = NULL;
		tempData1->child = (struct bTreeDataNode**)malloc(sizeof(struct bTreeDataNode*)*(nodeSize+1));

		tempData2 = (struct bTreeDataNode*)malloc(sizeof(struct bTreeDataNode));
		tempData2->val = (int*)malloc(sizeof(int)*nodeSize);
		tempData2->size = 0;
		tempData2->parent = NULL;
		tempData2->child = (struct bTreeDataNode**)malloc(sizeof(struct bTreeDataNode*)*(nodeSize+1));
		for(k = 0; k <= nodeSize; ++k)
		{
			*(tempData1->child + k) = *(tempData2->child + k) = NULL;
		}
		

		//coping the value across the nodes
		for( j = 0; j < nodeSize/2 ; ++j)
		{
			if(j != i)
			{
				*(tempData1->val + j) = *(dataRoot->val + j);
				if(j != i+1)
				{
					*(tempData1->child + j) = *(dataRoot->child + j);
					if(*(tempData1->child +j) != NULL)
					{
						(*(tempData1->child + j))->parent = tempData1;
					}
				}
			}
			else
			{
				*(tempData1->val + j) = priVal;
				if(childNode != NULL)
				{
					*(dataRoot->child + i) = *(childNode->child);
					*(dataRoot->child + i + 1) = *(childNode->child + 1);
					(*(childNode->child))->parent = (*(childNode->child + 1))->parent = dataRoot;
					
					*(tempData1->child + j) = *(childNode->child);
					*(tempData1->child + j + 1) = *(childNode->child + 1);

					if(*(tempData1->child + j) != NULL)
					{
						(*(tempData1->child + j))->parent = (*(tempData1->child + j + 1))->parent = tempData1;
					}
				}
			}
		}
		tempData1->size = j;

		if(j != i)
		{
			*(dataRoot->val) = *(dataRoot->val + j);
			if(j != i+1)
			{
				*(tempData1->child + j) = *(dataRoot->child + j);
				if(*(tempData1->child +j) != NULL)
				{
					(*(tempData1->child + j))->parent = tempData1;
				}
			}
		}
		else
		{
			*(dataRoot->val) = priVal;
			if(childNode != NULL)
			{
				*(dataRoot->child + i) = *(childNode->child);
				*(dataRoot->child + i + 1) = *(childNode->child + 1);
				(*(childNode->child))->parent = (*(childNode->child + 1))->parent = dataRoot;
				
				*(tempData1->child + j) = *(childNode->child);
				*(tempData2->child + childCounter) = *(childNode->child + 1);

				if(*(tempData1->child + j) != NULL)
				{
					(*(tempData1->child + j))->parent = tempData1;
					(*(tempData2->child + childCounter))->parent = tempData2;
				}
			}
			++childCounter;
		}
		dataRoot->size = 1;

		for( ++j,k = 0; j <= nodeSize ; ++j,++k)
		{
			if(j != i)
			{
				*(tempData2->val + k) = *(dataRoot->val + j);
				if(j != i+1)
				{
					*(tempData2->child + childCounter) = *(dataRoot->child + j);
					if(*(tempData2->child + childCounter) != NULL)
					{
						(*(tempData2->child + childCounter))->parent = tempData2;
					}
					++childCounter;
				}
			}
			else
			{
				*(tempData2->val + k) = priVal;

				if(childNode != NULL)
				{
					*(dataRoot->child + i) = *(childNode->child);
					*(dataRoot->child + i + 1) = *(childNode->child + 1);
					(*(childNode->child))->parent = (*(childNode->child + 1))->parent = dataRoot;
	
					*(tempData2->child + childCounter) = *(childNode->child);
					*(tempData2->child + childCounter + 1) = *(childNode->child + 1);

					if(*(tempData2->child + childCounter) != NULL)
					{
						(*(tempData2->child + childCounter))->parent = (*(tempData2->child + childCounter + 1))->parent = tempData2;
					}

				}
				childCounter+=2;
			}
		}
		tempData2->size = k;

		//keeping up the child parent relationship
		tempData1->parent = tempData2->parent = dataRoot;
		*(dataRoot->child) = tempData1;
		*(dataRoot->child + 1) = tempData2;
	}

	return dataRoot;
}

struct bTreeDataNode* insertToBTreeTree(struct bTreeNode *root,int priVal)
{
	struct bTreeDataNode *tempDNode = bTreeInserterroot(root->dataRoot,root->nodeSize,priVal);
	if(tempDNode != NULL)
	{
		root->dataRoot = tempDNode;
		// tempDNode->parent = NULL;
	}
	return tempDNode;
}

void printBTreeTree(struct bTreeDataNode *dataRoot)
{
	int i;
	if(dataRoot == NULL)
	{
		return;
	}
	printf("\nme: %p , parent: %p , val: ",dataRoot,dataRoot->parent);
	for(i = 0; i < dataRoot->size; ++i)
	{
		printf("%d ", *(dataRoot->val +i) );
	}
	printf(", children: ");
	for(i = 0; i <= dataRoot->size; ++i)
	{
		printf("%p ", *(dataRoot->child + i) );
	}

	for(i = 0; i <= dataRoot->size; ++i)
	{
		printBTreeTree( *(dataRoot->child + i) );
	}
}

struct bTreeNode* deleteFromBSTTree(struct bTreeNode *root,int priVal)
{
	struct bTreeDataNode *dataRoot = root->dataRoot;
	int i,j;
	if(dataRoot == NULL)
	{
		return NULL;
	}
	for(i = 0; i < dataRoot->size; ++i)
	{
		if(*(dataRoot->val + i) == priVal)
		{
			if(*(dataRoot->child + i) == NULL && *(dataRoot->child + i + 1) == NULL)
			{
				for(j = i; j < dataRoot->size - 1; ++j)
				{
					*(dataRoot->val + j) = *(dataRoot + val + j + 1);
				}
				*(dataRoot->val + j) = NULL;
				return NULL;
			}
			else
			{
				//an intermediate node has the value so do the neccessary actions
				struct bTreeDataNode *preChild = *(dataRoot->child + i), *nextChild = *(dataRoot->child + i + 1);
				int t = (root->nodeSize + 1)/2;
				if(preChild->size >= t)
				{
					*(dataRoot->val + i) = *(preChild->val + preChild->size - 1);
					--(preChild->size);
					//to be done:what happens to the next child last child pointer before the movement. This comes in the following else if and else case also
				}
				else if(nextChild->size >= t)
				{
					*(dataRoot->val + i) = *(nextChild->val);
					for(j = 0; j < nextChild->size - 1 ; j++)
					{
						*(nextChild->val + j) = *(nextChild->val + j + 1);
						*(nextChild->child + j) = *(nextChild->child + j + 1);
					}
					*(nextChild->child + j) = *(nextChild->child + j + 1);
					--(nextChild->size);
				}
				else
				{
					//merging two nodes take care of the childrens properly
				}
			}
		}
		else if(*(dataRoot->val + i) > priVal)
		{
			//actually should check for t-1 values in this node and do the neccessary actions if not
			return deleteFromBSTTree(*(root->child + i),priVal);
		}
	}
	return deleteFromBSTTree(*(root->child + i),priVal);
}

struct bTreeNode* deleteFromBTreeTree(struct bTreeNode **root,int priVal)
{
	deleteFromBSTTree(*root,priVal);
	// rotateTree(root);
	// rootCorrector(root);
}
