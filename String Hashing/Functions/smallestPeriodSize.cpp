// O( |a| ) 
int smallestPeriodSize(StringHash a){
	int smallest_period_size = (int)a.size();
	int last_index = (int)a.size()-1;
	for (int x = 1; x <= a.size(); ++x) {
		if(a.size()%x == 0){
			if(a.forward_hash(0,last_index-x) == a.forward_hash(x,last_index)){
				smallest_period_size = min(smallest_period_size,x);
			}
		}
	}
	return smallest_period_size;
}
