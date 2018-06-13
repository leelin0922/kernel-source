Git 建立 Remote Branch 的相關指令操作 發表於 2013 年 11 月 20 日 由 Tsung Git 建立遠端的 Branch 要如何做呢?

Git 建立 Remote Branch 的相關指令操作 Git 遠端 Branch 的建立、操作、使用、刪除方式.

Git 建立 遠端 Branch

git clone git@github.com:user/project.git

cd project

git checkout -b new_branch # 建立 local branch

git push -u origin new_branch # 建立遠端 branch (將 new_branch 建立到遠端)

git fetch

vim index.html # 修改

git commit -m 'test' -a # commit

git push

註: new_branch 要換成你要的 branch name, 以上所有 new_branch 都要對應著修改成同樣名稱.

Git 使用 遠端 Branch

git clone git@github.com:user/project.git

cd project

git branch -r # 看遠端有什麼 branch

git checkout origin/new_branch -b new_branch # 建立 local new_branch 並與遠端連接

vim index.html # 修改

git commit -m 'test' -a # commit

git push

註: new_branch 要換成你要的 branch name, 以上所有 new_branch 都要對應著修改成同樣名稱.

Git 刪除 遠端 Branch

git push origin :new_branch # 刪除遠端的 branch

git push origin --delete new_branch # 刪除遠端的 branch

Git Branch 的 Merge

git branch new_branch # 建立 branch

git checkout new_branch # 切到 new_branch, git checkout -b new_branch 可以同時建立 + 切換

vim index.html # 修改

git commit -m 'test' -a # commit

git checkout master # 切回 master

git merge new_branch # 將 new_branch merge 到 master

git branch -d new_branch # 若砍不掉就用 -D

更新所有 Repository branch

git remote update

Git 兩人實際操作 Remote BRanch 範例

user1 建立 remote branch：先建立 local branch 再 push 產生 remote branch

git checkout -b new_branch # local 建立 new_branch

... git commit something ...

git push origin new_branch # 會自動建立新的 remote new_branch

git pull origin new_branch # 拉線上新版下來

user2 合作開發，拉下 remote new_branch 建立 local new_branch

git clone git@github.com:user/project.git

git co origin/new_branch -b new_branch # 連結 remote new_branch 成 local new_branch

git push origin new_branch # push 到 remote new_branch

git pull origin new_branch # 拉線上新版下來
