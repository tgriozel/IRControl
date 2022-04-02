const int b1 = 11;
const int b2 = 12;

void buttons_setup() {
    pinMode(b1, INPUT);
    pinMode(b2, INPUT);
}

int b1State, b2State = 0;    

bool is_b1_pushed(){
    b1State = digitalRead(b1);
    return b1State == HIGH;
}

bool is_b2_pushed() {
    b2State = digitalRead(b2);
    return b2State == HIGH;
}
