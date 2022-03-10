int bsearch_lower(int a[], int t)
{
    int lo = 0, hi = a.size()-1;
    while(lo < hi)
    {
        int mid = (lo+hi)/2;
        if (t <= a[mid])
            max = mid;
        else
            lo = mid+1;
    }

    return a[min] == t? min : -1;
}
//c++ equivalent for vectors:
//      low = lower_bound(v.begin(),v.end(), val)

