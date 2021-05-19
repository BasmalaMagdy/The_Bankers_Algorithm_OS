#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int n, m;   // n = row    ,  m = colomn
vector<int> safe_seq;

bool isSafe(vector<int>work, vector<bool> finish, vector<vector<int>> need, vector<vector<int>>allocation);
int request(vector<vector<int>>allocation, vector<vector<int>> max, vector<vector<int>> need , vector<int> available , vector<int>work, vector<bool> finish, int p_num);

int main()
{
	int num , state , p_num , f = 1 , max_flag = 1 , check_max = 0;
	bool safe;
	vector<vector<int>> max;
	vector<vector<int>> allocation;
	vector<vector<int>> need;
	vector<int> available , work;
	vector<bool> finish;

	while (f)
	{
		cout << "number of processes : ";
		cin >> n;
		cout << endl;
		cout << "number of resources : ";
		cin >> m;
		cout << endl;
		// get allocation array
		cout << "Allocation Matrix : " << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "P" << i << "   ";
			vector<int> v1;
			for (int j = 0; j < m; j++)
			{
				cin >> num;
				v1.push_back(num);
			}
			allocation.push_back(v1);
		}
		cout << endl;

		//  get max array
		while (max_flag)
		{
			cout << "Max Matrix : " << endl;
			for (int i = 0; i < n; i++)
			{
				cout << "P" << i << "   ";
				vector<int> v1;
				for (int j = 0; j < m; j++)
				{
					cin >> num;
					v1.push_back(num);
				}
				max.push_back(v1);

			}
			cout << endl;

			// check that max > allocation

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					if (max[i][j] < allocation[i][j])
					{
						check_max = 1;
					}
				}
			}
			if (check_max == 0)
			{
				max_flag = 0;
			}
			else
			{
				cout << "Allocation Matrix must be less than or equal Max Matrix" << endl << endl;
			}
		}
		
		// get available array
		cout << "Available Matrix : " << endl;
		for (int j = 0; j < m; j++)
		{
			cin >> num;
			available.push_back(num);
			work.push_back(num);
		}
		cout << endl;

		// calculate need array
		for (int i = 0; i < n; i++)
		{
			vector<int> v1;
			for (int j = 0; j < m; j++)
			{
				num = max[i][j] - allocation[i][j];
				v1.push_back(num);
			}
			need.push_back(v1);
		}

		cout << "Need Matrix : " << endl;
		cout << "    ";
		for (int j = 0; j < m; j++)
		{
			cout << "R" << j << "   ";
		}
		cout << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "P" << i << "   ";
			for (int j = 0; j < m; j++)
			{
				cout << need[i][j] << "    ";
			}
			cout << endl;
		}

		for (int i = 0; i < n; i++)
		{
			finish.push_back(false);
		}

		cout << endl;
		cout << "Do you want safe state ? " << endl << "Yes : 1   ,  No : 0" << endl;
		cin >> state;
		cout << endl;
		if (state == 1)
		{
			safe = isSafe(work, finish, need, allocation);
			if (safe)
			{
				cout << "Yes , Safe state <";
				for (int i = 0; i < n; i++)
				{
					if (i != (n - 1))
					{
						cout << "P" << safe_seq[i] << ",";
					}
					else
					{
						cout << "P" << safe_seq[i] << ">";
					}
				}
			}
			else
			{
				cout << "No" << endl;
			}
		}
		cout << endl;
		cout << endl;
		state = 0;
		cout << "Do you want immediate requests ? " << endl << "Yes : 1   ,  No : 0" << endl;
		cin >> state;
		cout << endl;
		if (state == 1)
		{
			cout << "Enter number of process  P: ";
			cin >> p_num;
			while (p_num > (n - 1))
			{
				cout << "number of process must be less than" << n;
				cin >> p_num;
			}
			request(allocation, max, need, available, work, finish, p_num);
		}

		cout << endl;
		cout << endl;
		state = 0;
		cout << "Do you want to repeat ? " << endl << "Yes : 1   ,  No : 0" << endl;
		cin >> state;
		if (state == 0)
		{
			f = 0;
		}

	}
	cout << "press any key to exit...\n";
	cin >> n;
	return 0;
}


bool isSafe(vector<int>work, vector<bool> finish,vector<vector<int>> need, vector<vector<int>>allocation)
{
	int counter = 0 ,flag , f = 0;

	while (counter < n)
	{
		flag = 0;
		for (int i = 0; i < n; i++)
		{
			f = 0;
			if (!finish[i])
			{
				int j;
				for (j = 0; j < m; j++)
				{
					if (need[i][j] > work[j])
					{
						f = 1;
						break;
					}
				}

				if (f == 0)
				{
					for (int k = 0; k < m; k++)
					{
						work[k] += allocation[i][k];
					}
					safe_seq.push_back(i);
					counter++;
                    
					finish[i] = true;
					flag = 1;
				}
			}
		}

		if (flag == 0)
		{
			return false;
		}
	}

	return true;
}

int request(vector<vector<int>>allocation, vector<vector<int>> max, vector<vector<int>> need, vector<int> available , vector<int>work, vector<bool> finish, int p_num)
{
	int num;
	bool safe;
	vector<int> req;
	for (int i = 0; i < m; i++)
	{
		cin >> num;
		req.push_back(num);
	}
	for (int i = 0; i < m; i++)
	{
		if (req[i] > need[p_num][i])
		{
			cout << "Error! , process has exceeded its maximum claim" << endl;
			return 0;
		}
	}

	for (int i = 0; i < m; i++)
	{
		if (req[i] > available[i])
		{
			cout << "process must wait, since resources are not available" << endl;
			return 0;
		}
	}

	for (int i = 0; i < m; i++)
	{
		available[i] -= req[i];
		allocation[p_num][i] += req[i];
		need[p_num][i] -= req[i];
		work[i] = available[i];
	}
	
	safe = isSafe(work, finish, need, allocation);
	if (safe)
	{
		cout << "Yes request can be granted with safe state , Safe state <P" << p_num << "req,";
		for (int i = 0; i < n; i++)
		{
			if (i != (n - 1))
			{
				cout << "P" << safe_seq[i] << ",";
			}
			else
			{
				cout << "P" << safe_seq[i] << ">";
			}
		}
	}
	else
	{
		cout << "No , request can't be granted " << endl;
	}
}