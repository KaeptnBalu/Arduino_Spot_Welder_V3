This is V3.3.3 of the Arduino Code

Improvements:

    fix slow progress bar drawing problem
    
    
You can also apply this fix to older versions of the Arduino Code. All you have to do is change this line of code in the drawProgress function:

        res = ++o->step > steps;

to these two lines:

        o->step = (int)(millis()-o->millis)/(o->time/steps);
        res = o->step > steps;    
