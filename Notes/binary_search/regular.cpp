int bsearch(int a[], int t)
{
    int lo = 0, hi = a.size()-1;
    while(lo <= hi)
    {
        int mid = (lo+hi)/2;
        if (t == a[mid])
            return mid;
        else if (t > a[mid])
            lo = mid+1;
        else
            hi = mid-1;
    }

    return -1;
}
