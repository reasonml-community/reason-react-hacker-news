Create Reason React App
===

![image](https://cloud.githubusercontent.com/assets/3802023/26065669/945afdb4-398c-11e7-827c-d5ecbb76d0af.png)

Still far from it but I think a good start. I always had an issue with just jumping in and building something with Reason as it felt like there is loads of config involved.

I simplified @chenglou's [example repo](https://github.com/chenglou/reason-react-example) a bit, big thanks to his amazing work!
It lowers the barrier at least for me, hope it's helpful for others too.

**One of the main goals of Reason is to make the tooling simple enough to not need such a tool.** 
This is a work in progress towards it.

For now this is more like a quick start to React Reason than a "create-reason-react-app", but the latter is the end goal of this project.
I am still very knew to the language and this is where I want to learn and explore.

### Getting started

1. Clone the repo
2. `yarn` or `npm install`
3. `yarn start` or `npm start`
4. Open browser and navigate to: http://localhost:8080/

### Intro

The project uses bucklescript build system and webpack under the hood. When you run `yarn start`, `bsb` will run in watch mode and in parallel webpack's dev server is started at http://localhost:8080/. Files build by `bsb` can be found in the `/lib` directory. The amazing thing about `bsb` is that it produces readable javascript files.
After these JS files are produced, `webpack-dev-server` uses them.

### But how can I actually build something in Reason React

I will be adding more guides and examples to this repo. But for now, please check out
@chenglou's repo with a few examples https://github.com/chenglou/reason-react-example.
There's also a lot of information on syntax and Reason itself on the official website: https://facebook.github.io/reason.

### Contribute

I'd like this to be a great "Get started..." place for Reason. Please submit feature requests, issues and pull requests. Feel free to contribute!





