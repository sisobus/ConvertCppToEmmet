namespace FenwickTreeRangeUpdate {
    private void update(int left, int right, int by) {
        internalUpdate(left, by, -by * (left - 1));
        internalUpdate(right, -by, by * right);
    }

    private void internalUpdate(int at, int mul, int add) {
        while (at < dataMul.length) {
            dataMul[at] += mul;
            dataAdd[at] += add;
            at |= (at + 1);
        }
    }

    private int query(int at) {
        int mul = 0;
        int add = 0;
        int start = at;
        while (at >= 0) {
            mul += dataMul[at];
            add += dataAdd[at];
            at = (at & (at + 1)) - 1;
        }
        return mul * start + add;
    }
}
