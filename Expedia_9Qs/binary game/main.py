def binaryGame(min_len, max_len, one_group, zero_group):
    if max_len<one_group and max_len<zero_group or min_len>max_len:
        return 0
    dp = [0] * (1+max_len)

    dp[0] =1
    # dp[1]=int(one_group==1) + int(zero_group==1)

    for i in range(1,1+max_len):

        if i-one_group>=0:
            dp[i]+=dp[i-one_group]

        if i-zero_group>=0:
            dp[i]+=dp[i-zero_group]

    return sum(dp[min_len:])


if __name__ == '__main__':
    print(binaryGame(1,3,2,1)) #6
    print(binaryGame(2, 7, 0, 3))  # 2
    print(binaryGame(1, 3, 0, 1))  # 3
    print(binaryGame(2, 7, 0, 1))  # 6
    print(binaryGame(2, 3, 1, 1))  # 12
    print(binaryGame(2, 3, 0, 1))  # 2
