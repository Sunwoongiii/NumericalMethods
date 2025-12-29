import random

leaders = ['나경환', '김동현', '김수혁']
members = ['최선웅', '김무현', '리선준', '박영현', '임소연', '심승헌', '장채연', '김예빈','최준혁', '이태원', '최예빈', '고석범', '김승범', '김연우', '김주영', '박준영', '이명세', '허기환']

num_teams = len(leaders)
random.shuffle(members)
teams = {leader: [] for leader in leaders}
for i, member in enumerate(members):
    leader = leaders[i % num_teams]
    teams[leader].append(member)

for leader, member_list in teams.items():
    print(f"[{leader} 팀]")
    for member in member_list:
        print(member)
    print()
