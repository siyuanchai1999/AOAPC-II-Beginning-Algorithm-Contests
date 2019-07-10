//UVa822 - Queue and A
//Accepted 0.010s
//#define _XIENAOBAN_
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
#include<map>
#define MI 2147483647
using namespace std;

struct T {
	int ti;	//time for per task
	queue<int> table;
} ttmp;
struct P {
	int id, at, st, n, to[22];//identity, available time, start time of last task, number of topics, topics
	bool operator< (const P& that) const {
		if (st != that.st) return st < that.st;
		return id < that.id;
	}
} ptmp;

int Tpc, Psnl;//Number of Topics & Personnel
int name, num, nt, to, Scenario(0);

int main()
{
#ifdef _XIENAOBAN_
#define gets(T) gets_s(T, 80)
	freopen("in.txt", "r", stdin);
#endif
	ptmp.at = 0;
	while (scanf("%d", &Tpc) != EOF && Tpc != 0) {
		int time(MI), needtime(0);
		map<int, T> tpc;
		for (int i(0);i < Tpc;++i) {
			scanf("%d%d%d%d%d", &name, &num, &nt, &ttmp.ti, &to);
			if (time > nt) time = nt;
			auto& now(tpc[name] = ttmp);
			for (int i(0);i < num;++i)
				now.table.push(nt), nt += to;
		}
		scanf("%d", &Psnl);
		vector<P> psnl(Psnl);
		for (int i(0);i < Psnl;++i) {
			scanf("%d%d", &ptmp.id, &ptmp.n);
			for (int j(0);j < ptmp.n;++j)
				scanf("%d", ptmp.to + j);
			psnl[i] = ptmp;
		}
		while (Tpc) {
			int jumpt = MI;//Jump time to the earliest possible available time of all the men
			sort(psnl.begin(), psnl.end());
			for (auto& p : psnl) {//For all staff members
				int pti(MI);//Man's earliest possible available time
				if (p.at > time) pti = p.at;//Man is busy
				else {						//Man is available
					for (int i(0);i < p.n;++i) {//For all topics that man can handle
						auto& t(tpc[p.to[i]]);
						if (t.table.empty()) continue;							//Man find current topic finished
						if (t.table.front() <= time) {							//Man find his topic
							pti = time + t.ti;
							if (needtime < pti) needtime = pti;
							p.st = time;
							t.table.pop();
							if (t.table.empty()) --Tpc;
							break;
						}
						else if (t.table.front() < pti) pti = t.table.front();	//Man find current topic will be available at t.table.front()
					}
					p.at = pti;
				}
				if (pti < jumpt) jumpt = pti;
			}
			time = jumpt;
		}
		printf("Scenario %d: All requests are serviced within %d minutes.\n", ++Scenario, needtime);
	}
	return 0;
}