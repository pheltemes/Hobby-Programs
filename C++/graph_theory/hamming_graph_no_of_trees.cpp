#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> matrixcide(vector<vector<int>> x,vector<vector<int>> y,vector<vector<int>> z)
{
  int size_vec = x.size();
  vector<vector<int>> new_vec(3*size_vec, vector<int>(x[0].size()+1,0));
  int w = 0;
  for( int i = 0; i < size_vec; i++)
    {
      new_vec[i+w*size_vec][0]=w;
      for( int j = 0; j < x[i].size(); j++)
	{
	  new_vec[i+w*size_vec][j+1]=x[i][j];
	}
    }
  w++;
  for( int i = 0; i < size_vec; i++)
    {
      new_vec[i+w*size_vec][0]=w;
      for( int j = 0; j < y[i].size(); j++)
        {
          new_vec[i+w*size_vec][j+1]=y[i][j];
        }
    }
  w++;
  for( int i = 0; i < size_vec; i++)
    {
      new_vec[i+w*size_vec][0]=w;
      for( int j = 0; j < z[i].size(); j++)
        {
          new_vec[i+w*size_vec][j+1]=z[i][j];
        }
    }
  return new_vec;
}



struct vertex
{
  vector<int>vertex_nums; // vertex numbers
  vector<vertex*>adj_list;
  int graph_num; // 0,1 or 2
  int temp_graph_num;
  bool visited = 0; //to check if cyclic/connected
};

void reset(vector<vertex*> v)
{
  for(int i = 0; i< v.size(); i++)
    {
      v[i]->temp_graph_num = v[i]->graph_num;
      v[i]->visited=0;
    }
}

void printnode(vector<int> x, int y)
{
  for(int i = 0; i<x.size(); i++)
    {
      cout<<x[i];
    }
  cout<<"->"<<y<<endl;
}


bool is_tree(vector<vertex*> v, int graph_num, int starting_num)
{
  //cout<<v[starting_num]->temp_graph_num<<endl;
  queue<vertex*> q;
  vertex* currentnode;
  q.push(v[starting_num]);
  int count;
  int nodes_travelled = 0;
  while(!q.empty())
    {
      count = 0;
      nodes_travelled++;
      currentnode= q.front();
      q.pop();
      currentnode->visited=1;
      //cout<<currentnode->vertex_nums[0]<<currentnode->vertex_nums[1]<<currentnode->vertex_nums[2]<<endl;
      //cout<<currentnode->adj_list.size()<<endl;
      for(int i=0; i<currentnode->adj_list.size(); i++)
	{
	  if(currentnode->adj_list[i]->temp_graph_num == graph_num)
	    {
	      if(currentnode->adj_list[i]->visited == 1)
		{
		  count++;
		  if(count>1)
		    {
		      //cout<<"cycle"<<endl;
		      return 0;
		    } 
		}
	      else
		{
		  q.push(currentnode->adj_list[i]);
		}
	    }
	}
    }
  if(nodes_travelled == v.size()/3)
    {
      //cout<<nodes_travelled<<endl;
      return 1;
    }
  else
    {
      //cout<<"disconnected"<<endl;
      //cout<<nodes_travelled<<endl;
      return 0;
    }
}




bool is_cover(vector<vertex*> verts)
{
  bool node = 0;
  int iterator = 0;
  int starting = 0;
  while(node == 0)
    {
      if(verts[iterator]->temp_graph_num==0)
	{
	  starting=iterator;
	  node =1;
	}
      iterator++;
    }
  if(is_tree(verts,0,starting)==0){return 0;}
  //cout<<"0 tree made"<<endl;
  node= 0;
  iterator = 0; //might be able to speed up
  starting = 0;
  while(node == 0)
    {
      if(verts[iterator]->temp_graph_num==1)
        {
	  starting=iterator;
          node=1;
	}
      iterator++;
    }
  if(is_tree(verts,1,starting)==0){return 0;}
  //cout<<"1 tree made "<<endl;
  node= 0;
  iterator = 0;//might be able to speed up                                                                                                                                          
  starting = 0;
  while(node == 0)
    {
      if(verts[iterator]->temp_graph_num==2)
        {
          starting=iterator;
          node=1;
        }
      iterator++;
    }
  if(is_tree(verts,2,starting)==0){return 0;}
  //cout<<"yeet"<<endl;
  return 1;
}

vector<vertex*> generate_next(vector<vertex*> l_prev)
{
  vector<vector<int>> r4;
  vector<vector<int>> g4;
  vector<vector<int>> b4;
  for(int i=0; i<l_prev.size(); i++)
    {
      if(l_prev[i]->temp_graph_num==0)
	{
	  r4.push_back(l_prev[i]->vertex_nums);
	}
      if(l_prev[i]->temp_graph_num==1)
	{
          g4.push_back(l_prev[i]->vertex_nums);
	}
      if(l_prev[i]->temp_graph_num==2)
	{
          b4.push_back(l_prev[i]->vertex_nums);
	}
    }
  vector<vector<int>>r_m = matrixcide(r4,g4,b4);
  vector<vector<int>>g_m = matrixcide(g4,b4,r4);
  vector<vector<int>>b_m = matrixcide(b4,r4,g4);
  int tree_size = r_m.size();
  for(int i=0; i<tree_size; i++)
    {
      for( int j=0; j<r_m[i].size(); j++)
        {
          cout<<r_m[i][j]<<" ";
        }
      cout<<endl;
    }
  vector<vertex*> list_m;
  for(int i = 0; i <tree_size; i++)
    {
      vertex* v = new vertex;
      v->graph_num = 0;
      v->temp_graph_num =0;
      v->vertex_nums = r_m[i];
      list_m.push_back(v);
    }
  for(int i = 0; i <tree_size; i++)
    {
      vertex* v = new vertex;
      v->graph_num = 1;
      v->temp_graph_num=1;
      v->vertex_nums = g_m[i];
      list_m.push_back(v);
    }
  for(int i = 0; i <tree_size; i++)
    {
      vertex* v = new vertex;
      v->graph_num = 2;
      v->temp_graph_num=2;
      v->vertex_nums = b_m[i];
      list_m.push_back(v);
    }
  cout<<list_m.size()<<endl;                                                                                                                                                       
  int list_size = list_m.size();
  int num_size=list_m[0]->vertex_nums.size();
  int count;
  //int edges = 0;                                                                                                                                                                   
  for(int i=0; i<list_size; i++)
    {
      for( int j=i+1; j<list_size; j++)
        {
          count=0;
          for( int x=0; x<num_size; x++)
            {
              if(list_m[i]->vertex_nums[x]==list_m[j]->vertex_nums[x]){count++;}
            }
          if(count==r4[0].size())
            {
              //edges++;                                                                                                                                                            
              list_m[i]->adj_list.push_back(list_m[j]);
              list_m[j]->adj_list.push_back(list_m[i]);
              //cout<<edges<<endl;                                                                                                                                                   
            }
        }
    }
  return(list_m);  
}

vector<vertex*> find_solution(vector<vertex*> list_m)
{
  int tree_size = list_m.size()/3;
  cout<<tree_size<<endl;
  int counter =0;
  for( int i=0; i<tree_size; i++) // tree_size
    {
      for( int j =0; j<tree_size; j++)
	{
	  if(i != j)
	    {
	      for( int ig=tree_size; ig<tree_size*2; ig++) // tree_size *2
		{
		  for( int jg =tree_size; jg<tree_size*2; jg++)
		    {
		      if(ig != jg)
			{
			  for( int ib=2*tree_size; ib<tree_size*3; ib++) //tree_size *3
			    {
			      for( int jb =2*tree_size; jb<tree_size*3; jb++)
				{
				  if(ib != jb)
				    {
				      list_m[i]->temp_graph_num = 1;
				      list_m[j]->temp_graph_num = 2; 
				      list_m[ig]->temp_graph_num = 0;
				      list_m[jg]->temp_graph_num = 2;
				      list_m[ib]->temp_graph_num = 0;
				      list_m[jb]->temp_graph_num = 1;
				      if(is_cover(list_m)==1)
					{
					  printnode(list_m[i]->vertex_nums,1);
					  printnode(list_m[j]->vertex_nums,2);
					  printnode(list_m[ig]->vertex_nums,0);
					  printnode(list_m[jg]->vertex_nums,2);
					  printnode(list_m[ib]->vertex_nums,0);
					  printnode(list_m[jb]->vertex_nums,1);
					  cout<<endl;
					  return(list_m);
					}
				      else
					{
					  reset(list_m);
					}
				      counter++;
				      if(counter % 1000000==0)
					{
					  cout<<counter<<endl;
					}
				      //cout<<jb<<endl; 
				    }
				  //cout<<ib<<endl;
				}
			      //cout<<ib<<endl;
			    }
			}
		    }
		}
	    }
	}
    } 
  cout<<"Shit"<<endl;
}

int main()
{
  vector<vector<int>>r = {{0,1},{0,0},{2,0}};
  vector<vector<int>>g = {{0,2},{1,2},{1,0}};
  vector<vector<int>>b = {{1,1},{2,1},{2,2}};
  vector<vector<int>>r_m = matrixcide(r,g,b);
  vector<vector<int>>g_m = matrixcide(g,b,r);
  vector<vector<int>>b_m = matrixcide(b,r,g);
  int tree_size = r_m.size();
  for(int i=0; i<tree_size; i++)
    {
      for( int j=0; j<r_m[i].size(); j++)
	{
	  cout<<r_m[i][j]<<" ";
	}
      cout<<endl;
    }
  vector<vertex*> list_m;
  for(int i = 0; i <tree_size; i++)
    {
      vertex* v = new vertex;
      v->graph_num = 0;
      v->temp_graph_num =0;
      v->vertex_nums = r_m[i];
      list_m.push_back(v);
    }
  for(int i = 0; i <tree_size; i++)
    {
      vertex* v = new vertex;
      v->graph_num = 1;
      v->temp_graph_num=1;
      v->vertex_nums = g_m[i];
      list_m.push_back(v);
    }
  for(int i = 0; i <tree_size; i++)
    {
      vertex* v = new vertex;
      v->graph_num = 2;
      v->temp_graph_num=2;
      v->vertex_nums = b_m[i];
      list_m.push_back(v);
    }
  //cout<<list_m.size()<<endl;
  int list_size = list_m.size();
  int num_size=list_m[0]->vertex_nums.size();
  int count;
  //int edges = 0;
  for(int i=0; i<list_size; i++)
    {
      for( int j=i+1; j<list_size; j++)
	{
	  count=0;
	  for( int x=0; x<num_size; x++)
	    {
	      if(list_m[i]->vertex_nums[x]==list_m[j]->vertex_nums[x]){count++;}
	    }
	  if(count==2)
	    {
	      //edges++;
	      list_m[i]->adj_list.push_back(list_m[j]);
	      list_m[j]->adj_list.push_back(list_m[i]);
	      //cout<<edges<<endl;
	    }
	}
    }
  int found=0;
  int countith=0;
  cout<<tree_size<<endl;
  while(found==0)
    {
      for( int i=0; i<tree_size; i++) //tree_size
	{
	  for( int j =0; j<tree_size; j++)
	    {
	      if(i != j)
		{
		  for( int ig=tree_size; ig<2*tree_size; ig++) //2* tree_size
		    {
		      for( int jg =tree_size; jg<2*tree_size; jg++)
			{
			  if(ig != jg)
			    {
			      for( int ib=2*tree_size; ib<3*tree_size; ib++) //3 * tree_size
				{
				  for( int jb =2*tree_size; jb<3*tree_size; jb++)
				    {
				      if(ib != jb)
					{
					  list_m[i]->temp_graph_num = 1;
					  list_m[j]->temp_graph_num = 2;
					  list_m[ig]->temp_graph_num = 0;
					  list_m[jg]->temp_graph_num = 2;
					  list_m[ib]->temp_graph_num = 0;
					  list_m[jb]->temp_graph_num = 1;
					  countith++;
					  if(is_cover(list_m)==1)
					    {
					      found=1;
					      printnode(list_m[i]->vertex_nums,1);
					      printnode(list_m[j]->vertex_nums,2);
                                              printnode(list_m[ig]->vertex_nums,0);
                                              printnode(list_m[jg]->vertex_nums,2);
                                              printnode(list_m[ib]->vertex_nums,0);
                                              printnode(list_m[jb]->vertex_nums,1);
					      goto end;
					      reset(list_m);
					    }
					  else
					    {
					      reset(list_m);
					    }
					  
					} 
				    }
				}
			    }
			}
		    }
		}
	    }
	}
      found=1;
      //cout<<1<<endl;
    }
  end:
  vector<vertex*> f4 =find_solution(generate_next(list_m));
  vector<vertex*> f5 =find_solution(generate_next(f4));
  vector<vertex*> f6 =find_solution(generate_next(f5));
}
