# How to contribute to this project?

To contribute to this project, please follow the steps below.

## 1. Create an issue to your request or choose an issue already defined

The easiest way to contribute to this project is by creating an issue. On the issues page, you will have 3 issues templates options to suggest a contribution: [Feature request (To request a new feature)](https://github.com/Dirack/vfsa/issues/new?assignees=Dirack&labels=enhancement&template=feature_request.md&title=%5BFEA%5D), [Documentation (to request a documentation update in README, new usage examples, wikis, etc)](https://github.com/Dirack/vfsa/issues/new?assignees=Dirack&labels=documentation&template=documentation.md&title=%5BDOC%5D) and [Bug report (to report bugs)](https://github.com/Dirack/vfsa/issues/new?assignees=Dirack&labels=bug&template=bug_report.md&title=%5BBUG%5D). Please choose one issue template and describe what do you really want in detail, use images, and code snippets if needed. Be clear in your request, and is not necessary to delete titles in the issues templates.   

If your contribution is for an issue already defined, please ignore this step.

## 2. Fork this project in <https://github.com/Dirack/vfsa/fork>

This is an open-source project, distributed bellow the GPL3 License. When you fork it, you automatically agree with the terms and conditions of the GPL3. So, before you push your contributions to this project, fork it, and read the usage license. 

## 3. Branch nomination and merging rules

### 3.1 Create a _branch_ for your contribution (name it using gitflow).

In your forked version of this project create a new branch. The branch name should be a reference to the issue you created in step 1 in the following way:

- For an issue of the type _Feature request_, the branch name should be **feature/issue/ID**
- For an issue of the type _Documentation request_, the branch name should be **documentation/issue/ID**
- For an issue of the type _Bug report_, the branch name should be **hotfix/issue/ID**

Where **ID** means the issue id number. Example, following this rule for the issue 22 the names above should be:

- For an issue of the type _Feature request_, the branch name should be **feature/issue/22**
- For an issue of the type _Documentation request_, the branch name should be **documentation/issue/22**
- For an issue of the type _Bug report_, the branch name should be **hotfix/issue/22**

The purpose of this nomination rule is to allow the developer to identify the issue related with the branch throughout the branch name.

### 3.2 Branch opening and merging rules

The default branch (main or master) and development branch names follow the rules below:

- The development branch is opened by the repository's administrator, and its name is **develop/VERSION** ('VERSION' means the current tag version being developed, example develop/1.1.0 means this branch is the development branch of the 1.1.0 version)

- The default branch is _main_ (or _master_) and only the repository's administrator can modify it

The branch merge follows _gitflow_ rules:

- These branches are opened and merged in the current development branch: _feature_, _documentation_, and _test_.

- These branches are opened and merged in _master_: _develop_, and _hotfix_.

- The branch _master_ receives modifications from _develop_ and bug corrections from _hotfix_

- The branch _develop_ receives modifications from any other branch, including bug corrections from _master_

## 4. Do clear _commit_ messages (a title with 50 characters and two paragraphs of text)

The commit history is so important as its content. This repository standard for commit messages is a maximum of 50 characters title and a maximum of 2 paragraphs of text in the commit message describing the modification. _Pull Requests_ with insufficient commit history will be rejected.

References to other commits are allowed and wanted, it is done adding the commit hash in the commit message.
And a reference to the issue is required, it is done adding #ID ('ID' means issue id number) in the title of the commit message or text. Please check out the commit message example below with a reference to issue 3 and commit 228cc06:

```
Program morse - send email through terminal #3

Morse uses sendemail to send email messages through bash terminal.
The interface is based on Dialog now. This commit resolves dependencies
problems in commit 228cc06
```

If your modification is small, one variable name, or code line, for example, the commit message can have only the title. Avoid comments in the code to explain your modification, this can be done in the commit message properly. If your explanation is quite long (more than two paragraphs), it is better to split your modification into two commits or more with shorter and clear commit messages.

If you add a new file, it is important to add descriptive headers in the top of your source code following the template below (This is an example for a python source code, though the required information are the same for all source files):

```py
#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Program Name (Python)
# 
# Purpose: Test vfsa program in multiple interfaces model.
# 
# Site: https://www.geofisicando.com
# 
# Programmer: Rodolfo A C Neves (Dirack) 26/03/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.
```

## 5. _Push_ your contribution to this repository

After you check your modifications and commit history are following the required steps above, you can push them to your forked version of this repository with the following command (substitute \<type\> for _feature_, _documentation_ or _hotfix_, as described in step 3):

```sh
~$ git push origin <type>/issue/ID
```

Then do a _pull request_ from this '\<type\>/issue/ID' branch in your repository to the correct branch in this repository: your base branch and destine branch names should follow the rules described in step 3.

## 6. Create a new _Pull Request_ with a clear description of your contribution

When you click in the "pull request" button you will be redirected to a pull request template, please fill in this template with a clearer and detailed description of your modifications, use images and code snippets if you want. You do not need to delete the titles in the template. 

There are some tips to increase the probability of your modifications acceptance:  Add usage examples and automatic unit tests to your contribution. You can also document these examples in a README.md and group that in a separate directory. If they are unit tests, describe expected results and acceptance criteria in the README and pull request.
