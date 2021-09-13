 ref.size(); ll mid;
    while (a != b) {
      mid = (a + b) / 2;
      
      // test party a->mid and i
      cout << "building output: " << endl; 
      for (ll x = 0; x <= mid; x++) {
        cout << ref[x] << " ";
      }
      cout << 3 << endl;

      fflush(stdout);
      cin >> res;

      if (res == mid-a+2) {
        b = mid;
      }
      else {
        a = mid + 1;
      }
       



    }
    cout << "belon