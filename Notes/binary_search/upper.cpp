int bsearch_upper(int a[], int t)
{
    int lo = 0, hi = a.size()-1;
    while(lo < hi)
    {
        int mid = (lo+hi+1)/2;
        if (t >= a[mid])
            lo = mid;
        else
            hi = mid-1;
    }

    return a[min] == t? min : -1;
}
//c++ equivalent for vectors:
//      hi = upper_bound(v.begin(),v.end(), val)
